TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11

SOURCES += main.cpp \
    FF/readff.cpp \
    FF/readinput.cpp \
    FF/input.cpp \
    FF/buckingham.cpp \
    FF/potential.cpp \
    FF/lennardJones.cpp \
    FF/mix.cpp \
    FF/harmonic_bond.cpp \
    FF/harmonic_angle.cpp \
    FF/cgroup.cpp \
    FF/morse_bond.cpp \
    FF/harmonic_dihedral.cpp \
    FF/opls_dihedral.cpp \
    FF/coullong.cpp \
    FF/harmonic_improper.cpp \
    FF/cvff_improper.cpp \
    FF/fepatoms.cpp \
    topo/catom.cpp \
    topo/csystem.cpp \
    topo/cbond.cpp \
    topo/cangle.cpp \
    topo/cselection.cpp \
    topo/cmolecule.cpp \
    topo/isystem.cpp \
    topo/ccoordinates.cpp \
    topo/cdatareader.cpp \
    commandlineparser.cpp \
    topo/cdihederal.cpp \
    topo/cimproper.cpp \
    topo/cpdbreader.cpp \
    topo/cmeasure.cpp \
    topo/cdatawriter.cpp \
    topo/cxmlwriter.cpp \
    FF/csortpotential.cpp \
    FF/csite.cpp \
    topo/csystemsorter.cpp \
    FF/cffstream.cpp \
    FF/cmixatoms.cpp


HEADERS += \
    FF/readff.h \
    FF/readinput.h \
    FF/input.h \
    FF/buckingham.h \
    FF/lennardJones.h \
    FF/potential.h \
    FF/mix.h \
    FF/harmonic_bond.h \
    FF/harmonic_angle.h \
    FF/cgroup.h \
    FF/morse_bond.h \
    FF/harmonic_dihedral.h \
    FF/opls_dihedral.h \
    FF/help.h \
    FF/coullong.h \
    FF/harmonic_improper.h \
    FF/cvff_improper.h \
    FF/fepatoms.h \
    topo/catom.h \
    topo/csystem.h \
    topo/cbond.h \
    topo/cangle.h \
    topo/cselection.h \
    topo/cmolecule.h \
    topo/isystem.h \
    topo/ccoordinates.h \
    topo/cdatareader.h \
    commandlineparser.h \
    topo/cdihederal.h \
    topo/cimproper.h \
    topo/cpdbreader.h \
    topo/cmeasure.h \
    topo/cdatawriter.h \
    topo/cxmlwriter.h \
    cconstants.h \
    FF/csortpotential.h \
    FF/csite.h \
    topo/csystemsorter.h \
    FF/cffstream.h \
    FF/cmixatoms.h


