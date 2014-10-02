<h2>SafeExport.jsfl</h2>
This is an Adobe Flash IDE script depends on <a href="http://www.xjsfl.com">xJSFL</a> framework.
This script is used to export the FLA to SWF if you are under certain conditions:
<ul>
<li>You are going to use pre-compiled SWC files as external librarys</li>
<li>You are going to create MovieClips in the library which are going to inherit the classes defined in the SWC files</li>
<li>Of course you have to <em>uncheck</em> the 'Auto declare stage instance' in the publish setting</li>
</ul>
<h3>Background</h3>
<ul>
<li>The SWC files would be used as a dynamic runtime librarys to hold the common ABC(ActionScript Binary Code) data for just only one instance</li>
<li>The SWF files won't contain any ABC data which have already been involved by the SWC files after publishing</li>
<li>However, the default behaviour of the Flash IDE publishing will fail if there is a MovieClip in the library which inherits the classes defined in the SWC files</li>
<li>Reference: https://forums.adobe.com/thread/198821</li>
</ul>
