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
CC=g++
CCC=g++
CXX=g++
FC=gfortran
AS=nasm

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/integrityMain.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -fno-threadsafe-statics -Wall -Wextra -fno-exceptions -nostdinc -fno-strict-aliasing -fno-common -fno-stack-protector -nodefaultlibs
CXXFLAGS=-O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -fno-threadsafe-statics -Wall -Wextra -fno-exceptions -nostdinc -fno-strict-aliasing -fno-common -fno-stack-protector -nodefaultlibs

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=-f elf

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/integrity_checker

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/integrity_checker: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	ld -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/integrity_checker ${OBJECTFILES} ${LDLIBSOPTIONS} -T ./scripts/link.ld -o "./bin/integrit_checker"

${OBJECTDIR}/integrityMain.o: integrityMain.asm 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -g -o ${OBJECTDIR}/integrityMain.o integrityMain.asm

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/integrity_checker

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
