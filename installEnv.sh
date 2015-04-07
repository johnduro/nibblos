
#!/bin/zsh

[ -d /tmp/nibbler_install_tmp_dir ] || mkdir /tmp/nibbler_install_tmp_dir

[ -d /tmp/nibbler_install_tmp_dir ] && echo "tmp directory created"

if
	[ -d ~/Library/Frameworks/SDL2.framework ] ;
then
	echo "SDL2.framework already here" ;
else
	curl -# --progress-bar https://www.libsdl.org/release/SDL2-2.0.3.dmg > /tmp/nibbler_install_tmp_dir/SDL2.framework.dmg ;
	hdiutil attach -mountpoint /tmp/nibbler_install_tmp_dir/sdl2_MP  /tmp/nibbler_install_tmp_dir/SDL2.framework.dmg ;
	cp -R /tmp/nibbler_install_tmp_dir/sdl2_MP/SDL2.framework ~/Library/Frameworks/SDL2.framework ;
	hdiutil detach /tmp/nibbler_install_tmp_dir/sdl2_MP ;
	echo "SDL2.framework .. OK" ;
fi

########################################################

if
	[ -d ~/Library/Frameworks/SDL2_ttf.framework ] ;
then
	echo "SDL2_ttf.framework already here" ;
else
	curl -# --progress-bar https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.dmg > /tmp/nibbler_install_tmp_dir/SDL2_ttf.framework.dmg ;
	hdiutil attach -mountpoint /tmp/nibbler_install_tmp_dir/sdl2_MP  /tmp/nibbler_install_tmp_dir/SDL2_ttf.framework.dmg ;
	cp -R /tmp/nibbler_install_tmp_dir/sdl2_MP/SDL2_ttf.framework ~/Library/Frameworks/SDL2_ttf.framework ;
	hdiutil detach /tmp/nibbler_install_tmp_dir/sdl2_MP ;
	echo "SDL2_ttf.framework .. OK" ;
fi

########################################################

if
	[ -d ~/Library/Frameworks/SDL2_image.framework ] ;
then
	echo "SDL2_image.framework already here" ;
else
	curl -# --progress-bar https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.dmg > /tmp/nibbler_install_tmp_dir/SDL2_image.framework.dmg ;
	hdiutil attach -mountpoint /tmp/nibbler_install_tmp_dir/sdl2_MP  /tmp/nibbler_install_tmp_dir/SDL2_image.framework.dmg ;
	cp -R /tmp/nibbler_install_tmp_dir/sdl2_MP/SDL2_image.framework ~/Library/Frameworks/SDL2_image.framework ;
	hdiutil detach /tmp/nibbler_install_tmp_dir/sdl2_MP ;
	echo "SDL2_image.framework .. OK" ;
fi

########################################################

if
	[ -f ./libraries/lib_fmod/lib/libfmod.dylib ] && [ -f ./libraries/lib_fmod/lib/libfmodL.dylib ] && [ -d ./includes/fmod ];
then
	echo "fmod dylib already exist" ;
else
	curl -# --progress-bar http://www.fmod.org/download/fmodstudio/api/Mac/fmodstudioapi10515mac-installer.dmg > /tmp/nibbler_install_tmp_dir/fmodstudioapi10515mac-installer.dmg ;
	hdiutil attach -mountpoint /tmp/nibbler_install_tmp_dir/fmod_MP  /tmp/nibbler_install_tmp_dir/fmodstudioapi10515mac-installer.dmg  ;
	cp -R /tmp/nibbler_install_tmp_dir/fmod_MP/FMOD\ Programmers\ API/api/lowlevel/inc ./includes/fmod ;
	cp -R /tmp/nibbler_install_tmp_dir/fmod_MP/FMOD\ Programmers\ API/api/lowlevel/lib ./libraries/lib_fmod/lib ;
	hdiutil detach /tmp/nibbler_install_tmp_dir/fmod_MP ;
	echo "SDL2_image.framework .. OK" ;
fi

########################################################

if
	[ -d ./libraries/lib_opengl/glm ] ;
then
	echo "glm already exist" ;
else
	curl -L -O -# --progress-bar http://sourceforge.net/projects/ogl-math/files/glm-0.9.6.3/glm-0.9.6.3.zip/download ;
	unzip -q download ;
	rm download ;
	mv "glm" "libraries/lib_opengl/glm" ;
	echo "GLM ... OK"
fi

[ -d /tmp/nibbler_install_tmp_dir ] && rm -rf /tmp/nibbler_install_tmp_dir
