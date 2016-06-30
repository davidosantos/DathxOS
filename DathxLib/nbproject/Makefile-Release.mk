#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Drivers.o \
	${OBJECTDIR}/io/in.o \
	${OBJECTDIR}/io/out.o \
	${OBJECTDIR}/memory/memory.o \
	${OBJECTDIR}/system/Providers/Messaging.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -fno-threadsafe-statics -Wall -Wextra -fno-exceptions -nostdinc -fno-strict-aliasing -fno-common -fno-stack-protector -nodefaultlibs
CXXFLAGS=-O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -fno-threadsafe-statics -Wall -Wextra -fno-exceptions -nostdinc -fno-strict-aliasing -fno-common -fno-stack-protector -nodefaultlibs

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdathxlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdathxlib.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdathxlib.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdathxlib.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdathxlib.a

${OBJECTDIR}/Drivers.o: Drivers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Drivers.o Drivers.cpp

${OBJECTDIR}/io/in.o: io/in.cpp 
	${MKDIR} -p ${OBJECTDIR}/io
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/io/in.o io/in.cpp

${OBJECTDIR}/io/out.o: io/out.cpp 
	${MKDIR} -p ${OBJECTDIR}/io
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/io/out.o io/out.cpp

${OBJECTDIR}/memory/memory.o: memory/memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/memory/memory.o memory/memory.cpp

${OBJECTDIR}/system/Providers/Messaging.o: system/Providers/Messaging.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/Providers
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/Providers/Messaging.o system/Providers/Messaging.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdathxlib.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
