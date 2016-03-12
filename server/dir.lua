--Directory utilities

function file_list_proc(dir,func)
	--dir path /s > temp.txt
	local tmpfile='temp.txt'
	os.execute('dir "'..dir..'" /s>'..tmpfile)
	io.input("temp.txt")

	local count=0	
	local dirname = ""
	local filename = ""
	local proclist={}
	for line in io.lines() do
		local a,b,c

		--directory match
		a,b,c=string.find(line,"^%s*(.+)%s+的目录")
		if a then
			dirname = string.gsub(c,'\\','/')
		end
	
		--file match
		a,b,c=string.find(line,"^%d%d%d%d%-%d%d%-%d%d%s-%d%d:%d%d%s-[%d%,]+%s+(.+)%s-$")
		if a then
			filename = c
		else
			--another date format
			a,b,c=string.find(line,"^%d%d%d%d%/%d%d%/%d%d%s-%d%d:%d%d%s-[%d%,]+%s+(.+)%s-$")
			if a then
				filename = c
			end
		end
		if filename and func then
			if not string.find(filename,tmpfile) then
				local file=dirname..'/'..filename
				if func(file) then
					table.insert(proclist,file)
				end
			end
		end
		count=count+1
	end
	return proclist
--	io.close()
--	os.execute('del '..tmpfile)
end

--获取指定的最后一个字符的位置
function get_last_word(all,word)
	local b = 0
	local last = nil
	while true do
		local s,e = string.find(all, word, b) -- find 'next' word
		if s == nil then
			break
		else
			last = s
		end
		b = s + string.len(word)
	end
	return last
end

function split_path(file)
	local last=get_last_word(file,'/')
	local path=string.sub(file,1,last)
	local name=string.sub(file,last+1)
	return path,name
end

function file_copy(src,dst)
	local fsrc=io.open(src,'r')
	local fdst=io.open(dst,'w')
	local data=fsrc:read('*a')
	fdst:write(data)
	fsrc:close()
	fdst:close()
end

function pwd()
	--dir path /s > temp.txt
	local tmpfile='temp1.txt'
	os.execute('dir>'..tmpfile)
	io.input("temp.txt")

	local count=0	
	local dirname = ""
	local filename = ""
	local proclist={}
	for line in io.lines() do
		local a,b,c

		--directory match
		a,b,c=string.find(line,"^%s*(.+)%s+的目录")
		if a then
			dirname = string.gsub(c,'\\','/')
			return dirname..'/'
		end
	end
	return '.'
end
