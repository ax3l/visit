// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                                ViewerProxy.C                              //
// ************************************************************************* //

#include <ViewerProxy.h>

#include <PlotPluginInfo.h>
#include <PlotPluginManager.h>
#include <OperatorPluginInfo.h>
#include <OperatorPluginManager.h>

#include <ClientInformation.h>
#include <ClientMethod.h>
#include <DebugStream.h>
#include <ImproperUseException.h>
#include <ParentProcess.h>
#include <PlotInfoAttributes.h>
#include <PluginManagerAttributes.h>
#include <RemoteProcess.h>
#include <SILRestrictionAttributes.h>
#include <SocketConnection.h>
#include <ViewerMethods.h>
#include <ViewerRPC.h>
#include <ViewerState.h>
#include <VisItException.h>
#include <Xfer.h>
#include <JSONNode.h>

#include <cstring>
#include <cstdlib>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif


static void CloseSocket(int fd);

// ****************************************************************************
// Method: CreateViewerProxy 
//
// Programmer: Hari Krishnan
// Creation:   October 18, 2011
//
// Purpose:
//        New method to construct ViewerProxy objects. Allows other libraries
//        to override construction of the ViewerProxy method..
//        if no other library has overriden the globalProxy variable
//        then it simply constructs a new ViewerProxy class..
//        Warning: Overriding more than one proxy will need care..
// Modifications:
// ****
ViewerProxy* ViewerProxy::CreateViewerProxy(ViewerProxy* proxy)
{
    
    static ViewerProxy* globalProxy = NULL;

    //if user has sent in a global proxy override the current one..
    if(proxy)
       globalProxy = proxy;

    //if globalProxy has been assigned return that otherwise
    //create a new ViewerProxy class..
    if(globalProxy)
       return globalProxy;

    //construct default ViewerProxy
    return new ViewerProxy();
}


// ****************************************************************************
// Method: ViewerProxy constructor
//
// Programmer: Eric Brugger
// Creation:   August 4, 2000
//
// Modifications:
//   Brad Whitlock, Fri Feb 9 18:15:39 PST 2007
//   I rewrote the method so it uses ViewerState and ViewerMethods and I
//   removed old modification comments.
//
//   Brad Whitlock, Tue Jun 24 11:23:36 PDT 2008
//   Added plot and operator plugin managers.
//
// ****************************************************************************

ViewerProxy::ViewerProxy() : SimpleObserver(), argv()
{
    viewer = 0;
    viewerP = 0;
    xfer = new Xfer;

    state = new ViewerState;
    methods = new ViewerMethods(state);

    plotPlugins = 0;
    operatorPlugins = 0;

    // Make the proxy observe the SIL restriction attributes.
    state->GetSILRestrictionAttributes()->Attach(this);

    animationStopOpcode = 0;
    iconifyOpcode = 0;
}

// ****************************************************************************
// Method: ViewerProxy destructor
//
// Programmer: Eric Brugger
// Creation:   August 4, 2000
//
// Modifications:
//   Brad Whitlock, Fri Feb 9 18:18:36 PST 2007
//   I rewrote the method so it uses ViewerState and I removed old modification
//   comments.
//
//   Brad Whitlock, Tue Jun 24 11:23:36 PDT 2008
//   Added plot and operator plugin managers.
//
// ****************************************************************************

ViewerProxy::~ViewerProxy()
{
    delete viewer;
    delete viewerP;
    delete xfer;
    delete state;
    delete methods;
    delete plotPlugins;
    delete operatorPlugins;
}

// ****************************************************************************
// Method: ViewerProxy::GetViewerState
//
// Purpose: 
//   Returns the ViewerState state objects.
//
// Returns:    Returns the ViewerState state objects.
//
// Programmer: Brad Whitlock
// Creation:   Tue Feb 13 11:39:16 PDT 2007
//
// Modifications:
//   
// ****************************************************************************

ViewerState *
ViewerProxy::GetViewerState() const
{
    return state;
}

// ****************************************************************************
// Method: ViewerProxy::GetViewerMethods
//
// Purpose: 
//   Returns the methods object.
//
// Returns:    Returns the methods object.
//
// Programmer: Brad Whitlock
// Creation:   Tue Feb 13 11:39:55 PDT 2007
//
// Modifications:
//   
// ****************************************************************************

ViewerMethods *
ViewerProxy::GetViewerMethods() const
{
    return methods;
}

// ****************************************************************************
// Method: ViewerProxy::Update
//
// Purpose: 
//   This method is called when objects that the ViewerProxy observes are
//   updated. This is an internal method and is primarily a means to update
//   the internal SIL restriction object.
//
// Arguments:
//   subj : A pointer to the subject that updated.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jun 21 13:23:50 PST 2001
//
// Modifications:
//   Hank Childs, Mon Dec  2 14:13:55 PST 2002
//   Create a new SIL restriction as a reference counted object from the heap.
//
//   Brad Whitlock, Fri Feb 9 18:19:41 PST 2007
//   Made it use ViewerState.
//
// ****************************************************************************

void
ViewerProxy::Update(Subject *subj)
{
    // If the SIL restriction attributes have changed, update the internal
    // SIL restriction object internalSILRestriction. This is done so the
    // internalSILRestriction is available to the client and we have to
    // make the conversion far less often.
    if(subj == state->GetSILRestrictionAttributes())
    {
        internalSILRestriction = new avtSILRestriction(
            *state->GetSILRestrictionAttributes());
    }
}

// ****************************************************************************
//  Method: ViewerProxy::GetReadConnection
//
//  Purpose:
//    Get the connection that the viewer reads from.
//
//  Returns:    The connection the viewer reads from.
//
//  Programmer: Eric Brugger
//  Creation:   August 4, 2000
//
//  Modifications:
//    Brad Whitlock, Tue May 3 15:46:49 PST 2005
//    Added viewerP.
//
// ****************************************************************************

Connection *
ViewerProxy::GetReadConnection() const
{
    if (viewer == 0 && viewerP == 0)
        return 0;

    if (viewer != 0)      
        return viewer->GetReadConnection();

    return viewerP->GetReadConnection();
}

// ****************************************************************************
//  Method: ViewerProxy::GetWriteConnection
//
//  Purpose:
//    Get the connection that the viewer writes to.
//
//  Returns:    The connection the viewer writes to.
//
//  Programmer: Eric Brugger
//  Creation:   August 4, 2000
//
//  Modifications:
//    Brad Whitlock, Tue May 3 15:46:49 PST 2005
//    Added viewerP.
//
// ****************************************************************************

Connection *
ViewerProxy::GetWriteConnection() const
{
    if (viewer == 0 && viewerP == 0)
        return 0;

    if(viewer != 0)
        return viewer->GetWriteConnection();

    return viewerP->GetWriteConnection();
}

// ****************************************************************************
// Method: ViewerProxy::GetLocalHostName
//
// Purpose: 
//   Returns the name of the local machine.
//
// Returns:    The name of the local machine.
//
// Programmer: Brad Whitlock
// Creation:   Mon Sep 24 11:32:45 PDT 2001
//
// Modifications:
//   Brad Whitlock, Tue May 3 15:49:40 PST 2005
//   Added viewerP.
//
// ****************************************************************************

const std::string &
ViewerProxy::GetLocalHostName() const
{
    if(viewer == 0 && viewerP == 0)
    {
        EXCEPTION1(VisItException, "Viewer not created.");
    }

    if(viewer != 0)
        return viewer->GetLocalHostName();

#if 0
    return viewerP->GetLocalHostName();
#else
    cerr << "Fix ViewerProxy::GetLocalHostName: " << __LINE__ << endl;
    return *(new std::string("localhost"));
#endif
}

// ****************************************************************************
// Method: ViewerProxy::GetLocalUserName
//
// Purpose: 
//   Returns the local user name.
//
// Returns:    The local user name.
//
// Programmer: Brad Whitlock
// Creation:   Thu Feb 21 10:06:52 PDT 2002
//
// Modifications:
//   Brad Whitlock, Tue May 3 15:49:57 PST 2005
//   Added viewerP.
//
//   Brad Whitlock, Wed Jan 11 17:03:46 PST 2006
//   I fixed the code for viewerP->GetLocalUseName.
//
// ****************************************************************************

const std::string &
ViewerProxy::GetLocalUserName() const
{
    if(viewer == 0 && viewerP == 0)
    {
        EXCEPTION1(VisItException, "Viewer not created.");
    }

    if(viewer != 0)
        return viewer->GetLocalUserName();

    return viewerP->GetLocalUserName();
}

// ****************************************************************************
//  Method: ViewerProxy::ProcessInput
//
//  Purpose:
//    Read data from the viewer and process it.
//
//  Programmer: Eric Brugger
//  Creation:   August 22, 2000
//
//  Modifications:
//    Brad Whitlock, Tue Apr 24 10:35:56 PDT 2001
//    Added code to detect that the viewer died.
//
//    Brad Whitlock, Wed Mar 20 17:45:28 PST 2002
//    I abstracted the read code.
//
//    Brad Whitlock, Tue May 3 15:52:06 PST 2005
//    I made it get the connection from xfer instead of viewer.
//
// ****************************************************************************

void
ViewerProxy::ProcessInput()
{
    //
    // Try and read from the viewer.
    //
    int amountRead = xfer->GetInputConnection()->Fill();

    //
    // Try and process the input.
    //
    if (amountRead > 0)
        xfer->Process();
}

// ****************************************************************************
// Method: ViewerProxy::AddArgument
//
// Purpose: 
//   Adds an argument to the viewer's argument list.
//
// Arguments:
//   arg : The argument to be added.
//
// Note:
//   This only has an effect if called before the Create call.
//
// Programmer: Brad Whitlock
// Creation:   Thu Sep 7 13:48:12 PST 2000
//
// Modifications:
//   Brad Whitlock, Fri Dec 20 11:53:23 PDT 2002
//   I made argv be a stringVector.
//
// ****************************************************************************

void
ViewerProxy::AddArgument(const std::string &arg)
{
    if(arg.size() == 0)
        return;

    argv.push_back(arg);
}

// ****************************************************************************
//  Method: ViewerProxy::Create
//
//  Purpose:
//    Create a viewer.
//
//  Programmer: Eric Brugger
//  Creation:   August 4, 2000
//
//  Modifications:
//    Brad Whitlock, Fri Feb 9 18:20:24 PST 2007
//    I made it use ViewerState and I removed old modification comments.
//
//    Jeremy Meredith, Thu May 24 10:16:39 EDT 2007
//    Added SSH tunneling argument to RemoteProcess::Open, set it to false.
//
//    Jeremy Meredith, Thu Feb 18 15:25:27 EST 2010
//    Split HostProfile int MachineProfile and LaunchProfile.
//
//    Eric Brugger, Mon May  2 17:18:18 PDT 2011
//    I added the ability to use a gateway machine when connecting to a
//    remote host.
//
//    Brad Whitlock, Tue Jun  5 16:09:54 PDT 2012
//    Use simpler RemoteProcess::Open.
//
// ****************************************************************************

void
ViewerProxy::Create(int *inputArgc, char ***inputArgv)
{
    Create("visit", inputArgc, inputArgv);
}

bool ViewerProxy::ConnectToExistingViewer(const std::string& host, const int& port, const std::string& password)
{

    //Step 1: Check and see if connection can be made..
    int testSocket = socket(AF_INET, SOCK_STREAM, 0);
    if( testSocket < 0 )
    {
        std::cerr << "Socket not created (ERROR)" << std::endl;
        return false;
    }

    std::cout << "connecting to host: " << host << " port " << port << std::endl;
    struct sockaddr_in sin;
    struct hostent *server = gethostbyname(host.c_str());
    memset(&sin, 0, sizeof(sin));
    memcpy(&(sin.sin_addr), server->h_addr, server->h_length);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    if (connect(testSocket,(struct sockaddr*) &sin,sizeof(sin)) < 0)
    {
        std::cerr << "Unable to connect to Viewer" << std::endl;
        CloseSocket(testSocket);
        return false;
    }

    //Step 2: Send password to verify that you should be added
    std::ostringstream handshake;
    handshake << "{ \"password\" : \"" << password << "\" }";

#ifndef _WIN32
    int nwrite = write(testSocket,handshake.str().c_str(),handshake.str().length());
#else
    int nwrite = _write(testSocket,handshake.str().c_str(),(unsigned int)handshake.str().length());
#endif
    if(nwrite < 0)
    {
        std::cerr << "Error writing to Viewer" << std::endl;
        CloseSocket(testSocket);
        return false;
    }

    //Step 3: receive arguments to establish reverse connection

    char buffer[1024];

#ifndef _WIN32
    int bytes = read(testSocket,buffer,1024);
#else
    int bytes = _read(testSocket,buffer,1024);
#endif
    buffer[bytes] = '\0';
    //std::cout << "bytes read: " << bytes << " " << buffer << std::endl;

    CloseSocket(testSocket);
    //Step 4: reverse connect same as if it was originally intented..

    //parse message and create new reverse connect

    std::string message = buffer;

    JSONNode node;
    node.Parse(message);

    stringVector args;

    args.push_back("-v");
    args.push_back(node.GetJsonObject()["version"].GetString());

    args.push_back("-host");
    args.push_back(node.GetJsonObject()["host"].GetString());

    args.push_back("-port");
    args.push_back(node.GetJsonObject()["port"].GetString());

    args.push_back("-key");
    args.push_back(node.GetJsonObject()["securityKey"].GetString());

    args.push_back("-reverse_launch");

    int inputArgc = args.size();

    char** inputArgv = new char* [inputArgc+1];

    for(size_t i = 0; i < args.size(); ++i)
    {
        inputArgv[i] = new char [args[i].length()+1];
        strcpy(inputArgv[i],args[i].c_str());
        inputArgv[i][args[i].length()] = '\0';
    }

    inputArgv[inputArgc] = NULL;

    // Connect to the viewer process. Our command line arguments
    // should contain  The viewer is executed using
    // "visit -viewer".
    //

    viewerP = new ParentProcess;
    viewerP->Connect(1, 1, &inputArgc, &inputArgv, true);

    // Use viewerP's connections for xfer.
    xfer->SetInputConnection(viewerP->GetWriteConnection());
    xfer->SetOutputConnection(viewerP->GetReadConnection());
    return true;
}


void
ViewerProxy::Create(const char *visitProgram, int *inputArgc, char ***inputArgv)
{
    //
    // Look for flags required for reverse launching.
    //
    bool haveRL = false;
    bool haveKey = false;
    bool havePort = false;

    //
    // check whether client wants to add itself to existing viewer
    // session
    //
    bool haveViewHost = false,
         haveViewPort = false,
         haveViewPassword = false;

    std::string add_viewer_host = "";
    int add_viewer_port = -1;
    std::string add_viewer_password = "";


    if(inputArgc != 0 && inputArgv != 0)
    {
        int count = *inputArgc;
        char **arg = *inputArgv;
        for(int i = 0; i < count; ++i)
        {
            if(strcmp(arg[i], "-reverse_launch") == 0)
                haveRL = true;
            else if(strcmp(arg[i], "-key") == 0)
                haveKey = true;
            else if(strcmp(arg[i], "-port") == 0)
                havePort = true;
            else if(strcmp(arg[i], "-viewer_host") == 0)
            {
                //TODO: handle command line args
                add_viewer_host = arg[i+1];
                haveViewHost = true;
                ++i;
            }
            else if(strcmp(arg[i], "-viewer_port") == 0)
            {
                add_viewer_port = atoi(arg[i+1]);
                haveViewPort = true;
                ++i;
            }
            else if(strcmp(arg[i], "-viewer_password") == 0)
            {
                add_viewer_password = arg[i+1];
                haveViewPassword = true;
                ++i;
            }
        }
    }
    bool addNewClientToViewer = haveViewHost &&
                                haveViewPort &&
                                haveViewPassword;
    bool reverseLaunch = haveRL && haveKey && havePort;

    if(!reverseLaunch)
    {
        if(!addNewClientToViewer)
        {
            //
            // Create the viewer process.  The viewer is executed using
            // "visit -viewer".
            //
            viewer = new RemoteProcess(std::string(visitProgram));
            viewer->AddArgument(std::string("-viewer"));

            //
            // Add any extra arguments to the viewer before opening it.
            //
            for (size_t i = 0; i < argv.size(); ++i)
                viewer->AddArgument(argv[i]);

            //
            // Open the viewer.
            //
            viewer->Open(MachineProfile::Default(), 1, 1);

            // Use viewer's connections for xfer.
            xfer->SetInputConnection(viewer->GetWriteConnection());
            xfer->SetOutputConnection(viewer->GetReadConnection());
        }
        else
        {
            std::cout << "Adding new client to viewer at :" << add_viewer_host << " "
                      << add_viewer_port << std::endl;
            if(!ConnectToExistingViewer(add_viewer_host,add_viewer_port,add_viewer_password))
            {
                EXCEPTION1(ImproperUseException, "ViewerProxy::Create called with invalid pre-existing Viewer information");

            }
        }
    }
    else
    {
        //
        // Connect to the viewer process. Our command line arguments
        // should contain  The viewer is executed using
        // "visit -viewer".
        //
        viewerP = new ParentProcess;
        viewerP->Connect(1, 1, inputArgc, inputArgv, true);

        // Use viewerP's connections for xfer.
        xfer->SetInputConnection(viewerP->GetWriteConnection());
        xfer->SetOutputConnection(viewerP->GetReadConnection());
    }

    //
    // Attach the AttributeSubjects to the xfer object. Note that the
    // plugin objects have not yet been added.
    //
    for(int i = 0; i < state->GetNumStateObjects(); ++i)
        xfer->Add(state->GetStateObject(i));

    xfer->ListObjects();

    // Create the special opcodes.
    animationStopOpcode = xfer->CreateNewSpecialOpcode();
    iconifyOpcode = xfer->CreateNewSpecialOpcode();
}

// ****************************************************************************
// Method: ViewerProxy::GetPlotPluginManager
//
// Purpose: 
//   Returns a pointer to the plot plugin manager.
//
// Arguments:
//
// Returns:    
//
// Note:       
//
// Programmer: Brad Whitlock
// Creation:   Tue Jun 24 11:36:05 PDT 2008
//
// Modifications:
//   
// ****************************************************************************

PlotPluginManager *
ViewerProxy::GetPlotPluginManager() const
{
    if(plotPlugins == 0)
    {
        EXCEPTION1(ImproperUseException, "ViewerProxy::InitializePlugins "
            "must be called before ViewerProxy::GetPlotPluginManager");
    }

    return plotPlugins;
}

// ****************************************************************************
// Method: ViewerProxy::GetOperatorPluginManager
//
// Purpose: 
//   Returns a pointer to the operator plugin manager.
//
// Arguments:
//
// Returns:    
//
// Note:       
//
// Programmer: Brad Whitlock
// Creation:   Tue Jun 24 11:36:27 PDT 2008
//
// Modifications:
//   
// ****************************************************************************

OperatorPluginManager *
ViewerProxy::GetOperatorPluginManager() const
{
    if(operatorPlugins == 0)
    {
        EXCEPTION1(ImproperUseException, "ViewerProxy::InitializePlugins "
            "must be called before ViewerProxy::GetOperatorPluginManager");
    }

    return operatorPlugins;
}

// ****************************************************************************
// Method: ViewerProxy::InitializePlugins
//
// Purpose: 
//   Creates and initializes the plugin managers.
//
// Arguments:
//   t         : The plugin type, which should be GUI or Scripting.
//   pluginDir : The plugin directory to use or NULL for the default.
//
// Returns:    
//
// Note:       The plugin managers are created if they do not yet exist.
//
// Programmer: Brad Whitlock
// Creation:   Tue Jun 24 11:29:07 PDT 2008
//
// Modifications:
//   
// ****************************************************************************

void
ViewerProxy::InitializePlugins(PluginManager::PluginCategory t, const char *pluginDir)
{
    if(plotPlugins == 0)
    {
        plotPlugins = new PlotPluginManager;
        plotPlugins->Initialize(t, false, pluginDir);
    }

    if(operatorPlugins == 0)
    {
        operatorPlugins = new OperatorPluginManager;
        operatorPlugins->Initialize(t, false, pluginDir);
    }
}

// ****************************************************************************
//  Method:  ViewerProxy::LoadPlugins
//
//  Purpose:
//    Unload and reload all the plugins
//
//  Programmer:  Jeremy Meredith
//  Creation:    September 26, 2001
//
//  Modifications:
//    Brad Whitlock, Mon Mar 25 13:00:10 PST 2002
//    I added code to print the list of connected objects to the log file.
//
//    Jeremy Meredith, Wed Aug 21 12:51:28 PDT 2002
//    I renamed some plot/operator plugin manager methods for refactoring.
//
//    Jeremy Meredith, Fri Feb 28 12:21:01 PST 2003
//    Renamed LoadPlugins to LoadPluginsNow (since there is a corresponding
//    LoadPluginsOnDemand).
//
//    Brad Whitlock, Fri Feb 9 18:22:54 PST 2007
//    I made it use ViewerState and I improved the exception error message.
//
//    Brad Whitlock, Tue Jun 24 11:29:29 PDT 2008
//    Use the new member plugin managers.
//
//    Brad Whitlock, Thu Jan  8 10:23:15 PST 2009
//    I registered the plot info attributes with xfer.
//
// ****************************************************************************

void
ViewerProxy::LoadPlugins()
{
    int nPlots = state->GetNumPlotStateObjects();
    int nOperators = state->GetNumOperatorStateObjects();
    if (nPlots > 0 || nOperators > 0)
    {
        debug1 << "Reloading plugins at runtime not supported\n";
        return;
    }

    if(plotPlugins == 0 || operatorPlugins == 0)
    {
        EXCEPTION1(ImproperUseException, "ViewerProxy::InitializePlugins "
            "must be called before ViewerProxy::LoadPlugins");
    }

    //
    // Go through the plugin atts and en/disable the ones specified
    // by the plugin attributes
    //
    PluginManagerAttributes *pluginManagerAttributes = state->GetPluginManagerAttributes();
    for (size_t i=0; i<pluginManagerAttributes->GetId().size(); i++)
    {
        if (! pluginManagerAttributes->GetEnabled()[i]) // not enabled
        {
            std::string id = pluginManagerAttributes->GetId()[i];
            if (pluginManagerAttributes->GetType()[i] == "plot")
            {
                if (plotPlugins->PluginExists(id))
                    plotPlugins->DisablePlugin(id);
            }
            else if (pluginManagerAttributes->GetType()[i] == "operator")
            {
                if (operatorPlugins->PluginExists(id))
                    operatorPlugins->DisablePlugin(id);
            }
        }
        else // is enabled -- it had better be available
        {
            std::string id = pluginManagerAttributes->GetId()[i];
            if (pluginManagerAttributes->GetType()[i] == "plot")
            {
                if (plotPlugins->PluginExists(id))
                    plotPlugins->EnablePlugin(id);
                else
                {
                    std::string msg(std::string("The ") + id + 
                        std::string(" plot plugin enabled by the viewer "
                            "was not available in the client."));
                    EXCEPTION1(VisItException, msg);
                }
            }
            else if (pluginManagerAttributes->GetType()[i] == "operator")
            {
                if (operatorPlugins->PluginExists(id))
                    operatorPlugins->EnablePlugin(id);
                else
                {
                    std::string msg(std::string("The ") + id + 
                        std::string(" operator plugin enabled by the viewer "
                            "was not available in the client."));
                    EXCEPTION1(VisItException, msg);
                }
            }
        }
    }

    //
    // Now load dynamic libraries
    //
    plotPlugins->LoadPluginsNow();
    operatorPlugins->LoadPluginsNow();

    //
    // Initialize the plot attribute state objects.
    //
    nPlots = plotPlugins->GetNEnabledPlugins();
    for (int i = 0; i < nPlots; ++i)
    {
        CommonPlotPluginInfo *info =
            plotPlugins->GetCommonPluginInfo(plotPlugins->GetEnabledID(i));
        AttributeSubject *obj = info->AllocAttributes();
        state->RegisterPlotAttributes(obj);

        xfer->Add(state->GetPlotAttributes(i));
        xfer->Add(state->GetPlotInformation(i));
    }

    //
    // Initialize the operator attribute state objects.
    //
    nOperators = operatorPlugins->GetNEnabledPlugins();
    for (int i = 0; i < nOperators; ++i)
    {
        CommonOperatorPluginInfo *info = 
            operatorPlugins->GetCommonPluginInfo(operatorPlugins->GetEnabledID(i));
        AttributeSubject *obj = info->AllocAttributes();
        state->RegisterOperatorAttributes(obj);
        xfer->Add(obj);
    }

    //
    // Print the list of connected objects to the log file.
    //
    xfer->ListObjects();
}

// ****************************************************************************
//  Method: ViewerProxy::Close
//
//  Purpose:
//    Terminate the viewer.
//
//  Programmer: Eric Brugger
//  Creation:   August 11, 2000
//
//  Modifications:
//    Brad Whitlock, Wed Apr 3 12:50:01 PDT 2002
//    Called a new method of RemoteProcess to wait for the viewer to quit.
//
//    Brad Whitlock, Tue May 3 16:04:17 PST 2005
//    Only wait for termination if we launched the viewer.
//
// ****************************************************************************

void
ViewerProxy::Close()
{
    // Tell the viewer to close.
    GetViewerMethods()->Close();

    //
    // Wait for the viewer to exit.
    //
    if(viewer != 0)
        viewer->WaitForTermination();
}

// ****************************************************************************
// Method: ViewerProxy::Detach
//
// Purpose: 
//   Tells the viewer to detach this client from the list of clients.
//
// Programmer: Brad Whitlock
// Creation:   Thu May 5 17:37:55 PST 2005
//
// Modifications:
//   
// ****************************************************************************

void
ViewerProxy::Detach()
{
    GetViewerMethods()->Detach();
}

// ****************************************************************************
// Method: ViewerProxy::InterruptComputeEngine
//
// Purpose: 
//   Interrupts the engine on the specified host.
//
// Arguments:
//   hostName : The host of the engine that we want to interrupt.
//
// Programmer: Brad Whitlock
// Creation:   Mon Apr 30 12:24:28 PDT 2001
//
// Modifications:
//    Jeremy Meredith, Tue Jul  3 15:10:28 PDT 2001
//    Changed the interruption mechanism.
//   
//    Jeremy Meredith, Tue Mar 30 11:07:45 PST 2004
//    Added a simulation name to the interfaces, as some engines now
//    can be simulations, meaning there might be more than one engine
//    per host.
//
// ****************************************************************************
void
ViewerProxy::InterruptComputeEngine(const std::string &hostName,
                                    const std::string &simName)
{
    xfer->SendInterruption(0);
}

// ****************************************************************************
//  Method: ViewerProxy::AnimationStop
//
//  Purpose:
//    Stop the active animation.
//
//  Programmer: Eric Brugger
//  Creation:   August 15, 2000
//
//  Modifications:
//    Brad Whitlock, Thu Feb 27 11:33:16 PDT 2003
//    I made this function also send a special opcode to stop the animation.
//
// ****************************************************************************

void
ViewerProxy::AnimationStop()
{
    //
    // Send a special opcode to stop the animation.
    //
    xfer->SendSpecialOpcode(animationStopOpcode);

    GetViewerMethods()->AnimationStop();
}

// ****************************************************************************
// Method: ViewerProxy::SetPlotSILRestriction
//
// Purpose: 
//   Tells the viewer to apply the SIL restriction to the selected plots in
//   the plot list.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jun 21 13:33:41 PST 2001
//
// Modifications:
//   
//   Hank Childs, Mon Dec  2 14:13:55 PST 2002
//   Account for the SIL restriction now being a pointer.
//
// ****************************************************************************

void
ViewerProxy::SetPlotSILRestriction()
{
    SILRestrictionAttributes *newSRA =internalSILRestriction->MakeAttributes();
    if(newSRA)
    {
        // Copy the attribute representation of the SIL restriction into the
        // silRestrictionAtts object and send notify observers. Note that
        // SetUpdate is set to false so the proxy's Update method is NOT called
        SILRestrictionAttributes *silRestrictionAtts = 
            state->GetSILRestrictionAttributes();
        *silRestrictionAtts = *newSRA;
        SetUpdate(false);
        silRestrictionAtts->Notify();

        // Now that the new SIL restriction attributes have been sent to the
        // viewer, send the RPC that tells the viewer to apply them.
        GetViewerMethods()->SetPlotSILRestriction();

        // Delete the new SRA since we're done with it.
        delete newSRA;
    }
}

// ****************************************************************************
// Method: ViewerProxy::SetPlotSILRestriction
//
// Purpose: 
//   Tells the viewer to apply the specified new SIL restriction to the
//   selected plots in the plot list.
//
// Arguments:
//   newRestriction the new SIL restriction.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jun 21 13:33:41 PST 2001
//
// Modifications:
//   
//   Hank Childs, Mon Dec  2 14:13:55 PST 2002
//   Account for the SIL restriction now being a pointer.
//
// ****************************************************************************

void
ViewerProxy::SetPlotSILRestriction(avtSILRestriction_p newRestriction)
{
    // Copy the new SIL restriction into the internal SIL restriction object.
    internalSILRestriction = newRestriction;

    SILRestrictionAttributes *newSRA =internalSILRestriction->MakeAttributes();
    if(newSRA)
    {
        // Copy the attribute representation of the SIL restriction into the
        // silRestrictionAtts object and send notify observers. Note that
        // SetUpdate is set to false so the proxy's Update method is NOT called
        SILRestrictionAttributes *silRestrictionAtts = 
            state->GetSILRestrictionAttributes();
        *silRestrictionAtts = *newSRA;
        SetUpdate(false);
        silRestrictionAtts->Notify();

        // Now that the new SIL restriction attributes have been sent to the
        // viewer, send the RPC that tells the viewer to apply them.
        GetViewerMethods()->SetPlotSILRestriction();

        // Delete the new SRA since we're done with it.
        delete newSRA;
    }
}

// ****************************************************************************
// Method: ViewerProxy::MethodRequestHasRequiredInformation
//
// Purpose: 
//   Looks at the current method request and determines if the method is
//   supported by the client and whether the method request has enough
//   information to support the method.
//
// Returns:    0 for method not supported
//             1 for method supported, not enough info
//             2 for method supported, enough info
//
// Note:       
//
// Programmer: Brad Whitlock
// Creation:   Thu May 5 20:04:16 PST 2005
//
// Modifications:
//   
// ****************************************************************************

int
ViewerProxy::MethodRequestHasRequiredInformation() const
{
    int retval;
    int index = state->GetClientInformation()->GetMethodIndex(
        state->GetClientMethod()->GetMethodName());

    if(index == -1)
    {
        // Method not supported.
        retval = 0;
    }
    else
    {
        std::string proto(state->GetClientInformation()->
            GetMethodPrototype(index));
        if(proto.size() < 1)
        {
            // Supported. Does not need args.
            retval = 2; 
        }
        else
        {
            size_t sCount = 0; 
            size_t dCount = 0;
            size_t iCount = 0;
            for(size_t i = 0; i < proto.size(); ++i)
            {
                if(proto[i] == 's')
                    ++sCount;
                else if(proto[i] == 'd')
                    ++dCount;
                else if(proto[i] == 'i')
                    ++iCount;
            }

            if(state->GetClientMethod()->GetIntArgs().size() >= iCount &&
               state->GetClientMethod()->GetDoubleArgs().size() >= dCount &&
               state->GetClientMethod()->GetStringArgs().size() >= sCount)
            {
                // Supported, has enough args.
                retval = 2;
            }
            else
            {
                // Supported, not enough args.
                retval = 1;
            }
        }
    }
 
    return retval;
}

// ****************************************************************************
// Method: ViewerProxy::SetXferUpdate
//
// Purpose: 
//   Sets Xfer's update flag.
//
// Arguments:
//   val : Whether updates should be allowed.
//
// Note:       This method allows a state object observer to send back
//             information to the viewer by following the following pattern:
//
//             SetXferUpdate(true);
//             obj->Notify();
//             SetXferUpdate(false);
//
//             Note that setting the xfer update flag to false after the
//             object's Notify method is important or the object that we're
//             observing will get back to the client. Be careful if the object
//             that you're Notifying has any other observers.
//
// Programmer: Brad Whitlock
// Creation:   Fri May 6 09:50:22 PDT 2005
//
// Modifications:
//   
// ****************************************************************************

void
ViewerProxy::SetXferUpdate(bool val)
{
    xfer->SetUpdate(val);
}


// ****************************************************************************
//  Method:  CloseSocket
//
//  Purpose:
//    Close a socket file descriptor.
//
//  Programmer:  Jeremy Meredith
//  Creation:    May 24, 2007
//
// ****************************************************************************
static void
CloseSocket(int fd)
{
    if (fd < 0)
        return;

#if defined(_WIN32)
    closesocket(fd);
#else
    close(fd);
#endif
}

