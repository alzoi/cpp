# Визуальная тема
Для активации темы необходимо в папкес исполняемым файлом разместить файл манифеста и скомпилировать программу.  
Файл манифеста должен быть в папке с исполняемым файлом.
Имя файла манифеста должно быть my_app.exe.manifest
```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">

	<assemblyIdentity version="1.0.0.0"
			  processorArchitecture="*"
	    		  name="CompanyName.ProductName.YourApplication"
	    		  type="win32"/>
	
	<description>Description</description>
	
	<dependency>
	    <dependentAssembly>
	        <assemblyIdentity type="win32"
	            		  name="Microsoft.Windows.Common-Controls"
	            		  version="6.0.0.0"
	            		  processorArchitecture="*"
	            		  publicKeyToken="6595b64144ccf1df"
	            		  language="*"/>
	    </dependentAssembly>
	</dependency>

</assembly>
```

![image](https://github.com/alzoi/cpp/assets/20499566/c9533a90-4ed1-48c0-8ac4-c472f46365b8)
