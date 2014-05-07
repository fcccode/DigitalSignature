
XMLSignps.dll: dlldata.obj XMLSign_p.obj XMLSign_i.obj
	link /dll /out:XMLSignps.dll /def:XMLSignps.def /entry:DllMain dlldata.obj XMLSign_p.obj XMLSign_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del XMLSignps.dll
	@del XMLSignps.lib
	@del XMLSignps.exp
	@del dlldata.obj
	@del XMLSign_p.obj
	@del XMLSign_i.obj
