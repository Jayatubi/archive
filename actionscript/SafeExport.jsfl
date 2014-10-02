xjsfl.init(this);
clear();

var exportSymbols = $$(":[linkageExportForAS=true]").elements;

var rootDir = document.pathURI;
rootDir = rootDir.substring(0, rootDir.lastIndexOf("/") + 1);

var generatedFileList = new Array();

for(var i = 0; i < exportSymbols.length; i++)
{
    var item = exportSymbols[i];
    
    if (item.linkageBaseClass.length > 0 && item.linkageBaseClass.indexOf("flash") != 0)    // Skip extends from native flash classes
    {
        var filePath = rootDir + item.linkageClassName + ".as";
        
        if (!FLfile.exists(filePath))   // Skip already exsits files, because that may already been handled by developer
        {
            trace("Generate file: " + filePath);
            
            var code =
            [
                "package {",
                "    import " + item.linkageBaseClass + ";",
                "    public dynamic class " + item.linkageClassName + " extends " + item.linkageBaseClass,
                "    {",
                "    }",
                "}"
            ].join("\n")
            FLfile.write(filePath, code);
            generatedFileList.push(filePath);
        }
    }
}

document.publish();

// Clear all the auto generated files
for(var i = 0; i < generatedFileList.length; i++)
{
    var filePath = generatedFileList[i];
    if (FLfile.exists(filePath))
    {
        FLfile.remove(filePath);
    }
}
