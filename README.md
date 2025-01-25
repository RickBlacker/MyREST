This is an Unreal Engine example that shows how to use C++ and HTTP to connect to a remote REST server and request and push data. 
There is a single blueprint called BP_APICaller.  This BP was added to the scene and shows up in the outliner.  BP_APICaller inherits from a C++ class that controls/kicks off all the HTTP logic. 
The app only prints resuts out to the UE log window.  There are three keyboard keys that control the behavior
Keypress 1: Gets a list of all users and prints results to UE log window
Keypress 2: Creates a new user, converts user object to JSON and posts to the HTTP rest.  Then display resuls from HTTP REST call, back to UE log window.
Keypress 3: Gets a single user from the HTTP REST call. 
