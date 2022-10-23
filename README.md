# simpleqtenginebrowser
The goal is to avoid tabs or bookmarks. Instead the program prints the current url on exit.
This suckless inspired approach is intended to make you script your own approach on how to handle your bookmarks/tabs.

You could for example use a relational database to keep track of categories, domains, timestamps, etc. 

No need to have 20 youtube tabs open, just query the youtube domain for videos you wanted to watch, when you have time again.

~~Todo: Context Menu to exit with the url of a selected link.~~
Further:
1. add the other page actions, like refresh, back and forth
1. maybe support more advanced features like download but maybe also not.
1. maybe make a version reading a page from stdin
1. optimize

#Important
Now, the entire profile path is set to the current working directory.
Link /home as home in ~/.local/share/QtNoobs/Qtw-Desktop/QtWebEngine.
This way your profile data will be written into the subfolder profile in your working directory.
If you do not create this symlink, the subfolder structure will be created inside of the .local folder.
