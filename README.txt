**Supports 5.0 Only**

Place the folder in one of the following directories:

A: {ProjectDirectory}/Plugins/

B: UE_5.0/Engine/Plugins/Marketplace/

# A will make the plugin available for 1 project.
# B will make the plugin available for all projects.

Editing the following line in the .uplugin file will enable the plugin by default for projects. *Only works for option B above*
"EnabledByDefault": false,	=>	"EnabledByDefault": true,

The plugin can be enabled/disabled in the Plugins window. To open this window, select Edit at the top then Plugins.
The plugin will be listed in Project(A) or Installed(B) as "CH Tools: Audio Total Duration".
Enabling/Disabling the plugin requires the editor to restart.

For instructions on how to use, see the included video.
