#! /bin/bash
echo 'component2c++.sh <Component> <Derivation>'

REPOSITORY_ROOT=$PWD

# gets the current git branch
#function parse_git_branch() {
#  git branch --no-color 2> /dev/null | sed -e '/^[^*]/d' -e "s/* \(.*\)/\1/" -e "s|origin\/|-|g"
#}

# get last commit hash prepended with @ (i.e. @8a323d0)
#function parse_git_hash() {
#  git rev-parse --short HEAD 2> /dev/null | sed "s/\(.*\)/@\1/"
#}
#GIT_BRANCH=$(parse_git_branch)$(parse_git_hash)

COMPONENTNAME=$1
DERIVATION=$2

cp ../Templates/ImplementationTemplate.cpp $1.cpp
cp ../Templates/HeaderTemplate.hpp $1.hpp
cp ../Templates/subdirTemplate.mk subdir.mk

sed -i 's/NAME/'$1'/g' $1.hpp
sed -i 's/NAME/'$1'/g' $1.cpp
sed -i 's/DIRECTORY/'$2'/g' subdir.mk
sed -i 's/NAME/'$1'/g' subdir.mk

if [ $2 ]
then
    mkdir Components/$2/$1
    mv $1.hpp Components/$2/$1
    mv $1.cpp Components/$2/$1
    mv subdir.mk Components/$2/$1/subdir.mk
    #insering the component into derivate
    
    meson rewrite target plainComponents add Components/$2/$1/$1.cpp

else
    mkdir Components/$1
    mv $1.hpp Components/$1
    mv $1.cpp Components/$1
    mv subdir.mk Components/$1/subdir.mk
    
    meson rewrite target plainComponents add Components/$1/$1.cpp
fi
