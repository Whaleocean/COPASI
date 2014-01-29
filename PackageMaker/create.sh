#!/bin/bash
# Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


# PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}
SORT=${COPASI_SORT:-sort}
PACKAGE=${COPASI_PACKAGE:-Windows}

COMMON_ENVIRONMENT=${COPASI_COMMON_ENVIRONMENT:-"/Users/shoops/environment/10.6"}
BUILD=${COPASI_BUILD:-"${COMMON_ENVIRONMENT}/package"}
SOURCE=${COPASI_SOURCE:-"${COMMON_ENVIRONMENT}/COPASI"}
SETUP_DIR=${COPASI_SETUP_DIR:-"${COMMON_ENVIRONMENT}/setup"}

PACKAGE_MAKER=${COPASI_PACKAGE_MAKER:-"/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker"}

major=`${AWK} -- '$2 ~ "COPASI_VERSION_MAJOR" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
minor=`${AWK} -- '$2 ~ "COPASI_VERSION_MINOR" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
build=`${AWK} -- '$2 ~ "COPASI_VERSION_BUILD" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
modified=`${AWK} -- '$2 ~ "COPASI_VERSION_MODIFIED" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
comment=`${AWK} -- '$2 ~ "COPASI_VERSION_COMMENT" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
buildname=${build}

if [ $modified == true ]; then
  buildname=${buildname}+
fi

MyAppVersion=${major}.${minor}.${build}

if [ x"${comment}" = x\"Snapshot\" ]; then
  MyAppVersion=${major}.
  [ ${#minor} = 1 ] && MyAppVersion=${MyAppVersion}0
  MyAppVersion=${MyAppVersion}${minor}.
  [ ${#build} = 1 ] && MyAppVersion=${MyAppVersion}0
  MyAppVersion=${MyAppVersion}${buildname}
fi

PACKAGE_NAME="COPASI-${MyAppVersion}-Darwin"

[ -e "${SETUP_DIR}" ] && rm -rf "${SETUP_DIR}"/*
mkdir -p "${SETUP_DIR}/${PACKAGE_NAME}"
pushd "${SETUP_DIR}/${PACKAGE_NAME}"

mkdir -p Applications/COPASI/

# Copy CopasiUI
echo cp -r "${BUILD}/copasi/CopasiUI/CopasiUI.app" Applications/COPASI/
cp -r "${BUILD}/copasi/CopasiUI/CopasiUI.app" Applications/COPASI/

# copy the Qt Framework into the image
pushd Applications/COPASI
echo macdeployqt CopasiUI.app/ -no-plugins
macdeployqt CopasiUI.app/ -no-plugins
popd

# Create the Info.plist file for CopasiUI
echo sed -e 's/%COPASI_VERSION%/'$major.$minor.$build'/g' \
  ${SOURCE}/copasi/CopasiUI/CopasiUI.plist '>' Applications/COPASI/CopasiUI.app/Contents/Info.plist
sed -e 's/%COPASI_VERSION%/'$major.$minor.$build'/g' \
  ${SOURCE}/copasi/CopasiUI/CopasiUI.plist > Applications/COPASI/CopasiUI.app/Contents/Info.plist

echo mkdir -p Applications/COPASI/CopasiUI.app/Contents/Resources
mkdir -p Applications/COPASI/CopasiUI.app/Contents/Resources

# copy the icon into the Resources directory
echo cp ${SOURCE}/copasi.icns Applications/COPASI/CopasiUI.app/Contents/Resources/
cp ${SOURCE}/copasi.icns Applications/COPASI/CopasiUI.app/Contents/Resources/

# copy the files for the wizard into the Resources directory
echo mkdir -p Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html
mkdir -p Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html

echo cp ${SOURCE}/copasi/wizard/help_html/*.html \
  Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html/
cp ${SOURCE}/copasi/wizard/help_html/*.html \
  Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html/

echo cp -r ${SOURCE}/copasi/wizard/help_html/figures \
  Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html/
cp -r ${SOURCE}/copasi/wizard/help_html/figures \
  Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html/

# add the license to the image
echo cp ${SOURCE}/copasi/ArtisticLicense.txt Applications/COPASI/License.txt
cp ${SOURCE}/copasi/ArtisticLicense.txt Applications/COPASI/License.txt

# copy the examples into the Resources directory
echo mkdir -p Applications/COPASI/examples
mkdir -p Applications/COPASI/examples

echo cp ${SOURCE}/TestSuite/distribution/* Applications/COPASI/examples/
cp ${SOURCE}/TestSuite/distribution/* Applications/COPASI/examples/

chmod 664 Applications/COPASI/examples/*
chmod 777 Applications/COPASI/examples

# copy default configuration
echo mkdir -p Applications/COPASI/config
mkdir -p Applications/COPASI/config
echo cp ${SOURCE}/copasi/MIRIAM/MIRIAMResources.xml Applications/COPASI/config
cp ${SOURCE}/copasi/MIRIAM/MIRIAMResources.xml Applications/COPASI/config
chmod 664 Applications/COPASI/config/*
chmod 777 Applications/COPASI/config

# copy the commandline version if it exists
echo cp ${BUILD}/copasi/CopasiSE/CopasiSE Applications/COPASI/
cp ${BUILD}/copasi/CopasiSE/CopasiSE Applications/COPASI/
strip Applications/COPASI/CopasiSE
chmod 755 Applications/COPASI/CopasiSE

popd

pushd ${SETUP_DIR}

mkdir copasi.pmdoc

# Create the index.html file
echo sed -e 's?%SOURCE%?'${SOURCE}'?g' \
    -e 's?%SETUP_DIR%?'${SETUP_DIR}'?g' \
    -e 's?%COPASI_VERSION%?'$major.$minor.$build'?g' \
    -e 's?%PACKAGE_NAME%?'${PACKAGE_NAME}'?g' \
  ${SOURCE}/PackageMaker/copasi.pmdoc/index.xml '>' copasi.pmdoc/index.xml

sed -e 's?%SOURCE%?'${SOURCE}'?g' \
    -e 's?%SETUP_DIR%?'${SETUP_DIR}'?g' \
    -e 's?%COPASI_VERSION%?'$major.$minor.$build'?g' \
    -e 's?%PACKAGE_NAME%?'${PACKAGE_NAME}'?g' \
  ${SOURCE}/PackageMaker/copasi.pmdoc/index.xml > copasi.pmdoc/index.xml

# Create the copasi.xml file
echo sed -e 's?%SOURCE%?'${SOURCE}'?g' \
    -e 's?%SETUP_DIR%?'${SETUP_DIR}'?g' \
    -e 's?%COPASI_VERSION%?'$major.$minor.$build'?g' \
    -e 's?%PACKAGE_NAME%?'${PACKAGE_NAME}'?g' \
  ${SOURCE}/PackageMaker/copasi.pmdoc/copasi.xml '>' copasi.pmdoc/copasi.xml

sed -e 's?%SOURCE%?'${SOURCE}'?g' \
    -e 's?%SETUP_DIR%?'${SETUP_DIR}'?g' \
    -e 's?%COPASI_VERSION%?'$major.$minor.$build'?g' \
    -e 's?%PACKAGE_NAME%?'${PACKAGE_NAME}'?g' \
  ${SOURCE}/PackageMaker/copasi.pmdoc/copasi.xml > copasi.pmdoc/copasi.xml

# Create the copasi-contents.xml file
echo sed -e 's?%SOURCE%?'${SOURCE}'?g' \
    -e 's?%SETUP_DIR%?'${SETUP_DIR}'?g' \
    -e 's?%COPASI_VERSION%?'$major.$minor.$build'?g' \
    -e 's?%PACKAGE_NAME%?'${PACKAGE_NAME}'?g' \
  ${SOURCE}/PackageMaker/copasi.pmdoc/copasi-contents.xml '>' copasi.pmdoc/copasi-contents.xml

sed -e 's?%SOURCE%?'${SOURCE}'?g' \
    -e 's?%SETUP_DIR%?'${SETUP_DIR}'?g' \
    -e 's?%COPASI_VERSION%?'$major.$minor.$build'?g' \
    -e 's?%PACKAGE_NAME%?'${PACKAGE_NAME}'?g' \
  ${SOURCE}/PackageMaker/copasi.pmdoc/copasi-contents.xml > copasi.pmdoc/copasi-contents.xml

# Run PackageMaker to create package
echo "${PACKAGE_MAKER}" \
  --doc "copasi.pmdoc" \
  --out "${PACKAGE_NAME}.pkg" 
"${PACKAGE_MAKER}" \
  --doc "copasi.pmdoc" \
  --out "${PACKAGE_NAME}.pkg"

# Hide the pkg extension
SetFile -a E "${PACKAGE_NAME}.pkg"

# Create a disk image
echo hdiutil create -volname "${PACKAGE_NAME}" -srcfolder "${PACKAGE_NAME}.pkg" -ov -format UDZO "${PACKAGE_NAME}"
hdiutil create -volname "${PACKAGE_NAME}" -srcfolder "${PACKAGE_NAME}.pkg" -ov -format UDZO "${PACKAGE_NAME}"
popd

