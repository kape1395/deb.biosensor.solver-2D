#!/bin/bash

MODE_BATCH=N
if [[ $1 == --batch ]] ; then
    MODE_BATCH=Y
fi


function get_prop() {
    local file=$1
    local name=$2
    cat $file | grep "^${name}=" | sed "s/^${name}=\(.*\)\$/\1/"
}


UPSTREAM_VERSION=$(get_prop build.properties upstream_version)
PACKAGING_SUFFIX=$(get_prop build.properties packaging_suffix)
PACKAGE_VERSION=${UPSTREAM_VERSION}${PACKAGING_SUFFIX}
CHANGELOG_VERSION=$(head -n 1  debian/changelog  | sed 's/.*(\(.*\)).*/\1/')

if [[ "${PACKAGE_VERSION}" != "${CHANGELOG_VERSION}" ]] ; then
    echo -ne "#\n# ERROR: Version in build.properties is different from that in debian/changelog.\n"
    echo -ne "#        Have you forgotten to update it? You can use the following command to edit it:\n"
    echo -ne "#        \$ dch -v ${PACKAGE_VERSION} \"Packaging upstream release version ${UPSTREAM_VERSION}.\"\n#\n"
    exit 1
fi

if [[ $BATCH_MODE == Y ]] ; then
    echo -ne "# Build will be executed in the batch mode\n#\n"
    echo "# UPSTREAM_VERSION=${UPSTREAM_VERSION}"
    echo "# PACKAGING_SUFFIX=${PACKAGING_SUFFIX}"
    echo "# PACKAGE_VERSION=${PACKAGE_VERSION}"
else
    echo -ne "# Build will be executed in the interactive mode\n#\n"
    echo "# UPSTREAM_VERSION=${UPSTREAM_VERSION}"
    echo "# PACKAGING_SUFFIX=${PACKAGING_SUFFIX}"
    echo "# PACKAGE_VERSION=${PACKAGE_VERSION}"
    # TODO: Ask several questions here.
fi


echo -ne "#\n# Create upstream source distribution...\n#\n"
rm -rf build
mkdir build
git submodule init
if [[ -d biosensor/.git ]] ; then
    echo -ne "#\n# Ok, have upstream source in the module \"biosensor\"\n"
else
    echo -ne "#\n# ERROR: Upstream source not found\n"
    exit 1
fi
( 
    cd biosensor
    git checkout $UPSTREAM_VERSION
    autoreconf --install
    ./configure "CXXFLAGS=-g -O0 -ansi -Wall -DLOG_LEVEL_DEBUG -DBOOST_FILESYSTEM_VERSION=2" --with-boost-filesystem=boost_filesystem-mt
    make
    make dist
    cp biosensor-${UPSTREAM_VERSION}.tar.gz ../build/biosensor_${UPSTREAM_VERSION}.orig.tar.gz
    git clean -fxd
    git reset --hard
)

echo -ne "#\n# Preparing pakage source...\n#\n"
(
    cd build
    tar -xzf biosensor_${UPSTREAM_VERSION}.orig.tar.gz
    cp -r ../debian biosensor-${UPSTREAM_VERSION}/
)

echo -ne "#\n# Building source DEB...\n#\n"
(
    cd build/biosensor-${UPSTREAM_VERSION}
    debuild -sa -S
    debuild -sa -b
)


