--Convert msvc project to Makefile

function vcxproj_parse()
	require('dir')
	local proclist=file_list_proc('',vcxproj_func)
	if proclist then
		makefile_modify(proclist)
	end
	
	if true then return end

	--Parse arg,arg is global pass from interpreter
	if arg then
		local file=arg[1]
		vcxproj_parse_file(file)
		for i=1,#arg do
			print('arg'..i..'='..arg[i])
		end
	else
		return
	end
end

function vcxproj_func(file)
	if file then
		local len=string.len(file)
		local ext='.vcxproj'
		local _,j=string.find(file,ext)
		if j==len then
			vcxproj_parse_file(file)
			return true
--[[
			print(file)
			local path
			path,file=split_path(file)
			print(path)
			print(file)
]]--
		end
	end
	return false
end

function vcxproj_parse_file(file)
	--Read vcproj
	local f=assert(io.open(file,'r'))
	local data=f:read('*a')
	f:close()
	
	local proj=prop_from_vcxproj(data,'','ProjectName')
	local buildmode=prop_from_vcxproj(data,'','ConfigurationType')
	local predef=prop_from_vcxproj(data,'-D','PreprocessorDefinitions')
	local incdir=prop_from_vcxproj(data,'-I','AdditionalIncludeDirectories')
	local depdir=prop_from_vcxproj(data,'-L','AdditionalLibraryDirectories')
	local deplib=prop_from_vcxproj(data,'-l','AdditionalDependencies')
	local inc=file_from_vcxproj(data,'<ClInclude Include=')
	local src=file_from_vcxproj(data,'<ClCompile Include=')
	
	print('File '..file..' parsed.')	
	local path,_=split_path(file)

	--copy template Makefile
	file_copy('Makefile.tmpl',path..'Makefile')
	
	--create Makefile.dep
	local fdep=io.open(path..'Makefile.dep','w')

	if proj then
		fdep:write('NAME= '..proj..'\n')
	end

	if buildmode then
		local bm='execute'
		if string.find(buildmode,'DynamicLibrary') then
			bm='dynamic'
		elseif string.find(buildmode,'StaticLibrary') then
			bm='static'
		end
		fdep:write('BUILDMODE='..bm..'\n')
	end

	if predef then
		fdep:write('CFLAGS+= '..predef..'\n')
	end

	if incdir then
--		incdir=string.gsub(incdir,'$%(ProjectDir%)',' -I%./')
		fdep:write('CFLAGS+= '..incdir..'\n')
	end

	if depdir then
		fdep:write('LDFLAGS+= '..depdir..'\n')
	end

	if deplib then
		fdep:write('LIBS+= '..deplib..'\n')
	end

	if src then
		fdep:write('SRCS=')
		for i,file in pairs(src) do
			fdep:write(' '..file)
		end
		fdep:write('\n')
	end
	if inc then
		fdep:write('INCS=')
		for i,file in pairs(inc) do
			fdep:write(' '..file)
		end
		fdep:write('\n')
	end
	fdep:close()
end

--parse include and source files with tag
--<ClInclude Include> and <ClCompile Include=>
function file_from_vcxproj(xml,desc)
	local s=1
	local tag
	local t={}
	while s do
		_,s,tag=string.find(xml,desc..'\"(.-)\"',s)
		if tag then
			--'\' => '/'
			tag=string.gsub(tag,'\\','/')
			table.insert(t,tag)
		end
	end
	return t
end

--parse additional properties
function prop_from_vcxproj(xml,sbl,desc)
	--capture from <desc>...</desc>
	local _,s,tag=string.find(xml,'<'..desc..'>(.-)</'..desc..'>',s)
	if tag then
		--remove '%(desc)'
		tag=string.gsub(tag,'%%%('..desc..'%)','')
		--replace '$(ProjectDir)' with './'
		tag=string.gsub(tag,'$%(ProjectDir%)','./')
		--remove duplecated and tail ';'
		tag=string.gsub(tag,';;',';')
		local len=string.len(tag)
		if string.find(tag,';',len) then tag=string.sub(tag,1,len-1) end
		--replace ';' with sbl
		tag=string.gsub(tag,';',' '..sbl)
		tag=sbl..tag
		--'\' => '/'
		tag=string.gsub(tag,'\\','/')
		return tag
	end
	return nil
end

function makefile_modify(proclist)
	local fdep=io.open('Makefile.dep','w')
	local make='MAKE_CMD='
	local make_clean='MAKE_CLEAN_CMD='
	local PWD=pwd()
	for i,file in pairs(proclist) do
		local path,_=split_path(file)
		local _,j=string.find(path,PWD)
		path=string.sub(path,j+1)
		local cmd='$(MAKE) -C '..path
		make=make..cmd..';'
		make_clean=make_clean..cmd..' clean;'
	end
	fdep:write(make..'\n'..make_clean)
end

vcxproj_parse()
