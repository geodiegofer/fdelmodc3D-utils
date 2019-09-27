#!/bin/bash

# Check input parameters
if [ "$#" -ne 1 ]; then
		echo "put_bashrc.sh: wrong number of input parameters. Exiting."
		echo "put_bashrc.sh install"
		echo "     Sets ROOT on source_me.sh; appends source ROOT/source_me.sh to bashrc."
		echo "put_bashrc.sh uninstall"
		echo "     Resets source_me.sh; deletes this repo's lines from bashrc."
		exit
fi

if [[ $1 == "install" ]]; then
	here=$(pwd)
	
	sed -i "4,4s|FDEL3DUTILSROOT$|FDEL3DUTILSROOT=$here/bin|g" source_me.sh

	echo "# fdelmodc3d utils source" >> ~/.bashrc
	echo "source $here/source_me.sh # fdelmodc3d utils source" >> ~/.bashrc

	echo "Sourced source_me executables and aliases to bashrc."	
	
elif [[ $1 == "uninstall" ]]; then
	sed -i "4,4s|FDEL3DUTILSROOT.*$|FDEL3DUTILSROOT|g" source_me.sh

	sed -i "/# fdelmodc3d utils source/d" ~/.bashrc
	
	echo "Removed source_me lines from bashrc."
else
	echo "Invalid option. Please choose 'install' or 'uninstall' "
fi
