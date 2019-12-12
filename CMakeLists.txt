#<===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
## File Name:    CMakeLists.txt
## Author:       Hao-Kai SUN
## Created:      2019-12-09 Mon 20:48:25 CST
## <<=====================================>>
## Last Updated: 2019-12-09 Mon 22:41:57 CST
##           By: Hao-Kai SUN
##     Update #: 18
## <<======== COPYRIGHT && LICENSE =======>>
##
## Copyright © 2019 SUN Hao-Kai <spin.hk@outlook.com>. All rights reserved.
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or (at
## your option) any later version.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
##
## ============================== CODES ==============================>>>
cmake_minimum_required(VERSION 3.15)

# apply CMake policies for specific CMake versions
if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.16)
endif()

project(
    HadronInfo
    VERSION 0.0.3
    DESCRIPTION "Some simple description about the project."
    LANGUAGES CXX
    )

# set C++ stand to 98/03 since all BOSS versions are developed
# using g++ compiler that not fully support C++11
set(CMAKE_CXX_STANDARD 98)

# output compile_commands.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set root path
set(BOSS_VERN "$ENV{HOME}/Work/664p03")
# set include paths' common parent
set(BOSS_PATH "${BOSS_VERN}/Boss")
set(BOSS_ELIB "${BOSS_VERN}/ExternalLib")
set(BOSS_WORK "${BOSS_VERN}/workarea")

# Set compiler for C
find_program(CMAKE_C_COMPILER gcc)
set(CMAKE_C_COMPILER
    "${CMAKE_C_COMPILER}"
    CACHE FILEPATH
    "The compiler for C language"
    FORCE
    )

# from `cmt show macro_value cflags`
set(CMAKE_C_FLAGS
    "-fmessage-length=0 -fPIC"
    CACHE STRING
    "The compiling flags for C compiler."
    FORCE
    )

# Set compiler for CPP
find_program(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_COMPILER
    "${CMAKE_CXX_COMPILER}"
    CACHE FILEPATH
    "The compiler for C++ language"
    FORCE
    )

# from `cmt show macro_value cppflags`
set(CMAKE_CXX_FLAGS
    "-fmessage-length=0     -Wall -Wextra -pthread  -Wno-deprecated -Wno-empty-body -D_GNU_SOURCE -pthread -pipe -ansi -pedantic -W -Wall -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long   -march=x86-64 -mtune=x86-64 -pedantic-errors -O2 -DEXTEND"
    CACHE STRING
    "The compiling flags for C++ compiler."
    )

# make shared library
add_library(
    ${PROJECT_NAME} SHARED
    src/OmegaInfo.cpp
    )


target_include_directories(
    ${PROJECT_NAME} BEFORE PUBLIC
    "${BOSS_VERN}/Utilities/HadronInfo/HadronInfo-00-00-02"
    # "${BOSS_WORK}/InstallArea/include/HadronInfo"
    "${BOSS_WORK}/InstallArea/include"
    "${BOSS_PATH}/InstallArea/include"
    "${BOSS_ELIB}/Gaudi/GAUDI_v21r6/x86_64-slc5-gcc43-clhep2.0.4.5/InstallArea/include"
    "${BOSS_PATH}/InstallArea/include/ReconEvent"
    "${BOSS_PATH}/InstallArea/include/BesDChain"
    "${BOSS_PATH}/Analysis/VertexFit/VertexFit-00-02-71/VertexDbSvc"
    "${BOSS_PATH}/Analysis/VertexFit/VertexFit-00-02-71/src/test"
    "${BOSS_PATH}/InstallArea/include/VertexFit"
    "${BOSS_PATH}/InstallArea/include/ParticleID"
    "${BOSS_PATH}/InstallArea/include/EvtRecEvent"
    "${BOSS_PATH}/InstallArea/include/MucRecEvent"
    "${BOSS_PATH}/Event/ExtEvent/ExtEvent-00-00-13"
    "${BOSS_PATH}/InstallArea/include/ExtEvent"
    "${BOSS_PATH}/Event/RawDataProviderSvc/RawDataProviderSvc-00-03-39"
    "${BOSS_PATH}/InstallArea/include/RawDataProviderSvc"
    "${BOSS_PATH}/Mdc/MdcRecEvent/MdcRecEvent-00-05-14"
    "${BOSS_PATH}/InstallArea/include/MdcRecEvent"
    "${BOSS_PATH}/Tof/TofCaliSvc/TofCaliSvc-00-01-05"
    "${BOSS_PATH}/InstallArea/include/TofCaliSvc"
    "${BOSS_PATH}/Tof/TofQElecSvc/TofQElecSvc-00-00-04"
    "${BOSS_PATH}/InstallArea/include/TofQElecSvc"
    "${BOSS_PATH}/Mdc/MdcCalibFunSvc/MdcCalibFunSvc-00-03-15"
    "${BOSS_PATH}/InstallArea/include/MdcCalibFunSvc"
    "${BOSS_PATH}/InstallArea/include/CalibSvc"
    "${BOSS_PATH}/Emc/EmcCalibConstSvc/EmcCalibConstSvc-00-00-10/EmcCalibConstSvc"
    "${BOSS_PATH}/InstallArea/include/EmcCalibConstSvc"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibROOTCnv/CalibROOTCnv-00-01-06"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibROOTCnv/CalibROOTCnv-00-01-06/src/cnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibROOTCnv/CalibROOTCnv-00-01-06/src/test"
    "${BOSS_PATH}/InstallArea/include/CalibROOTCnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibTreeCnv/CalibTreeCnv-00-01-12"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibTreeCnv/CalibTreeCnv-00-01-12/src/cnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibTreeCnv/CalibTreeCnv-00-01-12/src/test"
    "${BOSS_PATH}/InstallArea/include/CalibTreeCnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibMySQLCnv/CalibMySQLCnv-00-01-09"
    "${BOSS_PATH}/InstallArea/include/CalibMySQLCnv"
    "${BOSS_PATH}/InstallArea/include/CalibXmlCnvSvc"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibDataSvc/CalibDataSvc-00-01-03"
    "${BOSS_PATH}/InstallArea/include/CalibDataSvc"
    "${BOSS_PATH}/Tof/TofRecEvent/TofRecEvent-00-02-14"
    "${BOSS_PATH}/InstallArea/include/TofRecEvent"
    "${BOSS_PATH}/Emc/EmcRecEventModel/EmcRecEventModel-01-01-18"
    "${BOSS_PATH}/InstallArea/include/EmcRecEventModel"
    "${BOSS_PATH}/Event/DstEvent/DstEvent-00-02-50-p01"
    "${BOSS_PATH}/InstallArea/include/DstEvent"
    "${BOSS_PATH}/Event/McTruth/McTruth-00-02-19/McTruth"
    "${BOSS_PATH}/InstallArea/include/McTruth"
    "${BOSS_PATH}/Mdc/MdcRawEvent/MdcRawEvent-00-03-08"
    "${BOSS_PATH}/InstallArea/include/MdcRawEvent"
    "${BOSS_PATH}/Tof/TofRawEvent/TofRawEvent-00-02-07"
    "${BOSS_PATH}/InstallArea/include/TofRawEvent"
    "${BOSS_PATH}/InstallArea/include/EmcRawEvent"
    "${BOSS_PATH}/InstallArea/include/RawEvent"
    "${BOSS_PATH}/Event/EvTimeEvent/EvTimeEvent-00-00-08"
    "${BOSS_PATH}/InstallArea/include/EvTimeEvent"
    "${BOSS_PATH}/Mdc/DedxCorrecSvc/DedxCorrecSvc-00-02-52"
    "${BOSS_PATH}/InstallArea/include/DedxCorrecSvc"
    "${BOSS_PATH}/Mdc/MdcGeomSvc/MdcGeomSvc-00-01-37"
    "${BOSS_PATH}/InstallArea/include/MdcGeomSvc"
    "${BOSS_PATH}/Tof/TofCaliSvc/TofCaliSvc-00-01-05"
    "${BOSS_PATH}/InstallArea/include/TofQCorrSvc"
    "${BOSS_PATH}/InstallArea/include/MagneticField"
    "${BOSS_PATH}/Event/EventModel/EventModel-01-05-31"
    "${BOSS_PATH}/InstallArea/include/EventModel"
    "${BOSS_PATH}/Emc/EmcRecGeoSvc/EmcRecGeoSvc-01-01-07"
    "${BOSS_PATH}/InstallArea/include/EmcRecGeoSvc"
    "${BOSS_PATH}/InstallArea/include/EmcGeneralClass"
    "${BOSS_PATH}/InstallArea/include/MucGeomSvc"
    "${BOSS_PATH}/InstallArea/include/G4Geo"
    "${BOSS_PATH}/DetectorDescription/Identifier/Identifier-00-02-13"
    "${BOSS_PATH}/InstallArea/include/Identifier"
    "${BOSS_PATH}/Event/RelTable/RelTable-00-00-02"
    "${BOSS_PATH}/InstallArea/include/RelTable"
    "${BOSS_PATH}/InstallArea/include/RootPolicy"
    "${BOSS_PATH}/InstallArea/include/calibUtil"
    "${BOSS_PATH}/InstallArea/include/rdbModel"
    "${BOSS_PATH}/InstallArea/include/xmlBase"
    "${BOSS_PATH}/InstallArea/include/CalibData"
    "${BOSS_PATH}/InstallArea/include/facilities"
    "${BOSS_PATH}/InstallArea/include/DatabaseSvc"
    "${BOSS_PATH}/Emc/EmcWaveform/EmcWaveform-00-00-03/EmcWaveform"
    "${BOSS_PATH}/InstallArea/include/EmcWaveform"
    "${BOSS_PATH}/InstallArea/include/ROOTGeo"
    "${BOSS_PATH}/Simulation/BOOST/SimUtil/SimUtil-00-00-37/SimUtil"
    "${BOSS_PATH}/InstallArea/include/SimUtil"
    "${BOSS_PATH}/InstallArea/include/BesTimerSvc"
    "${BOSS_PATH}/InstallArea/include/DecayChain"
    "${BOSS_PATH}/BesCxxPolicy/BesCxxPolicy-00-01-01"
    "${BOSS_ELIB}/lcg/app/releases/ROOT/5.24.00b/x86_64-slc5-gcc43-opt/root/include"
    "${BOSS_PATH}/External/GdmlToRoot/GdmlToRoot-00-00-13/src"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Saxana"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Saxana/Saxana"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Processes"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Processes/Processes"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Schema"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Schema/Schema"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Writer"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Writer/Writer"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/ROOTBinding/Processor"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/ROOTBinding/Processor/Processor"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/ROOTBinding/Subscribers"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/ROOTBinding/Subscribers/Subscribers"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/ROOTBinding/Evaluator"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/ROOTBinding/Evaluator/Evaluator"
    "${BOSS_PATH}/External/BesROOT/BesROOT-00-00-07/src"
    "${BOSS_ELIB}/lcg/app/releases/ROOT/5.24.00b/x86_64-slc5-gcc43-opt/root/include"
    "${BOSS_ELIB}/lcg/external/Boost/1.39.0_python2.5/x86_64-slc5-gcc43-opt/include/boost-1_39"
    "${BOSS_PATH}/BesFortranPolicy/BesFortranPolicy-00-01-03/src"
    "${BOSS_PATH}/External/GdmlToG4/GdmlToG4-00-00-10/src"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Saxana"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Saxana/Saxana"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Processes/"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Processes/Processes"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Schema"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Schema/Schema"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Writer"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/Common/Writer/Writer"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Evaluator"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Evaluator/G4Evaluator"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Processor"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Processor/G4Processor"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Subscribers"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Subscribers/G4Subscribers"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Writer"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/G4Binding/G4Writer/G4Writer"
    "${BOSS_PATH}/External/BesGeant4/BesGeant4-00-00-09/src"
    "${BOSS_ELIB}/packages/geant4/4.9.3.p01/x86_64-slc5-gcc43-opt/geant4.9.3.p01/include"
    "${BOSS_PATH}/External/BesCLHEP/BesCLHEP-00-00-09/src"
    "${BOSS_ELIB}/packages/CLHEP/Alist/Alist-00-00-06"
    "${BOSS_ELIB}/packages/CLHEP/String/String-00-00-05"
    "${BOSS_ELIB}/packages/CLHEP/2.0.4.5/x86_64-slc5-gcc43-opt/include"
    "${BOSS_PATH}/External/CERNLIB/CERNLIB-01-02-02/src"
    "${BOSS_ELIB}/lcg/external/cernlib/2006a/x86_64-slc5-gcc43-opt/include"
    "${BOSS_ELIB}/lcg/external/HepMC/2.03.11/x86_64-slc5-gcc43-opt/include"
    "${BOSS_ELIB}/lcg/external/HepPDT/2.05.04/x86_64-slc5-gcc43-opt/include"
    "${BOSS_ELIB}/lcg/external/XercesC/2.8.0/x86_64-slc5-gcc43-opt/include"
    "${BOSS_PATH}/External/MYSQL/MYSQL-00-00-09/src"
    "${BOSS_ELIB}/lcg/external/mysql/5.0.18/x86_64-slc5-gcc43-opt/include"
    "${BOSS_ELIB}/lcg/external/mysql/5.0.18/x86_64-slc5-gcc43-opt/include/mysql"
    "${BOSS_ELIB}/lcg/external/sqlite/3.6.8/x86_64-slc5-gcc43-opt/include"
    "${BOSS_ELIB}/lcg/app/releases/LCGCMT/LCGCMT_57a_clhep2.0.4.5/LCG_SettingsCompat/src"
    "${BOSS_PATH}/DetectorDescription/GdmlManagement/GdmlManagement-00-00-31/src"
    "${BOSS_PATH}/External/BesExternalArea/BesExternalArea-00-00-21/src"
    )

# from `cmt show macro_value <PACKAGE_NAME>_shlibflags`
set(LIBNAMES
    "HadronInfo;ReconEvent;BesDChain;VertexFit;ParticleID;EvtRecEvent"
    "MucRecEvent;ExtEvent;RawDataProviderSvcLib;MdcRecEvent;TofCaliSvcLib"
    "TofQElecSvcLib;MdcCalibFunSvcLib;EmcCalibConstSvcLib;CalibROOTCnvLib"
    "CalibMySQLCnvLib;CalibXmlCnvSvcLib;CalibDataSvcLib;TofRecEvent"
    "EmcRecEventModel;DstEvent;McTruth;MdcRawEvent;TofRawEvent;EmcRawEvent"
    "RawEvent;EvTimeEvent;DedxCorrecSvcLib;MdcGeomSvcLib;DatabaseSvc"
    "TofQCorrSvcLib;EventModel;EmcRecGeoSvcLib;EmcGeneralClassLib"
    "MucGeomSvcLib;G4GeoLib;Identifier;calibUtil;rdbModel;xmlBase;CalibData"
    "facilities;EmcWaveform;ROOTGeoLib;SimUtil;BesTimerSvcLib;GaudiKernel"
    "Reflex;Processes;Saxana;Writer;Evaluator;Processor;Subscribers;MLP"
    "Minuit;Matrix;Physics;HistPainter;Hist;Rint;Core;RooFit;RooFitCore"
    "Tree;RIO;MathCore;Cint;RFIO;Graf;Graf3d;Gpad;Html;Postscript;Gui"
    "GX11TTF;GX11;ASImageGui;ASImage;Geom;GeomPainter;X3d;RGL;VMC;Table"
    "dequeDict;listDict;mapDict;map2Dict;multimapDict;multimap2Dict"
    "multisetDict;setDict;vectorDict;pthread;boost_system-gcc43-mt"
    "boost_filesystem-gcc43-mt;boost_regex-gcc43-mt;boost_thread-gcc43-mt"
    "gfortran;nsl;crypt;G4Evaluator;G4Processor;G4Subscribers;G4Writer"
    "G4baryons;G4biasing;G4bosons;G4brep;G4csg;G4cuts;G4decay;G4detector"
    "G4detscorer;G4detutils;G4digits;G4emadjoint;G4emhighenergy"
    "G4emlowenergy;G4empolar;G4emstandard;G4emutils;G4error_propagation"
    "G4event;G4FR;G4geombias;G4geomBoolean;G4geomdivision;G4geometrymng"
    "G4geomtext;G4gflash;G4gl2ps;G4globman;G4GMocren;G4graphics_reps"
    "G4had_im_r_matrix;G4had_lll_fis;G4had_mod_man;G4had_mod_util"
    "G4had_muon_nuclear;G4had_neu_hp;G4had_preequ_exciton"
    "G4hadronic_ablation;G4hadronic_abrasion;G4hadronic_bert_cascade"
    "G4hadronic_binary;G4hadronic_body_ci;G4hadronic_coherent_elastic"
    "G4hadronic_crosec_ci;G4hadronic_deex_evaporation"
    "G4hadronic_deex_fermi_breakup;G4hadronic_deex_fission"
    "G4hadronic_deex_gem_evaporation;G4hadronic_deex_handler"
    "G4hadronic_deex_management;G4hadronic_deex_multifragmentation"
    "G4hadronic_deex_photon_evaporation;G4hadronic_deex_util"
    "G4hadronic_em_dissociation;G4hadronic_fragm_ci;G4hadronic_HE"
    "G4hadronic_hetcpp_evaporation;G4hadronic_hetcpp_utils"
    "G4hadronic_incl_cascade;G4hadronic_interface_ci;G4hadronic_iso"
    "G4hadronic_LE;G4hadronic_leading_particle;G4hadronic_mgt"
    "G4hadronic_proc;G4hadronic_proc_ci;G4hadronic_qgstring;G4hadronic_qmd"
    "G4hadronic_radioactivedecay;G4hadronic_RPG;G4hadronic_stop"
    "G4hadronic_util;G4hadronic_xsect;G4had_string_diff;G4had_string_frag"
    "G4had_string_man;G4had_theo_max;G4hepnumerics;G4hits;G4intercoms"
    "G4ions;G4leptons;G4magneticfield;G4materials;G4mctruth;G4mesons"
    "G4modeling;G4muons;G4navigation;G4OpenGL;G4optical;G4parameterisation"
    "G4partadj;G4partman;G4partutils;G4phys_builders;G4phys_lists;G4procman"
    "G4RayTracer;G4readout;G4run;G4scoring;G4shortlived;G4specsolids"
    "G4tracking;G4track;G4transportation;G4Tree;G4UIbasic;G4UIcommon"
    "G4UIGAG;G4visHepRep;G4vis_management;G4visXXX;G4volumes;G4VRML;G4xrays"
    "Xm;CLHEP-Cast-2.0.4.5;CLHEP-Evaluator-2.0.4.5;CLHEP-Exceptions-2.0.4.5"
    "CLHEP-GenericFunctions-2.0.4.5;CLHEP-Geometry-2.0.4.5"
    "CLHEP-Random-2.0.4.5;CLHEP-RandomObjects-2.0.4.5"
    "CLHEP-RefCount-2.0.4.5;CLHEP-Vector-2.0.4.5;CLHEP-Matrix-2.0.4.5;Alist"
    "String;photos202;pythia6205;pdflib804;mathlib;pawlib;lapack3;blas"
    "graflib;grafX11;packlib;phtools;kernlib;X11;shift;LAPACK;BLAS;HepMC"
    "HepPDT;HepPID;xerces-c;xerces-depdom;mysqlclient_r;sqlite3"
)
set(LIBDIRS
    "${BOSS_WORK}/InstallArea/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_PATH}/InstallArea/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/Gaudi/GAUDI_v21r6/x86_64-slc5-gcc43-clhep2.0.4.5/InstallArea/x86_64-slc5-gcc43-opt/lib"
    # "${BOSS_WORK}/Utilities/HadronInfo/Utilities.xxma/HadronInfo/HadronInfo-00-00-02/x86_64-slc5-gcc43-opt/"
    "${BOSS_PATH}/Calibration/calibUtil/calibUtil-00-00-38/x86_64-slc5-gcc43-opt"
    "${BOSS_PATH}/Calibration/rdbModel/rdbModel-00-01-00/x86_64-slc5-gcc43-opt"
    "${BOSS_PATH}/Calibration/xmlBase/xmlBase-00-00-02/x86_64-slc5-gcc43-opt"
    "${BOSS_ELIB}/lcg/app/releases/ROOT/5.24.00b/x86_64-slc5-gcc43-opt/root/lib"
    "${BOSS_ELIB}/packages/BesGDML/2.8.0/x86_64-slc5-gcc43-opt/CPPGDML/lib"
    "${BOSS_ELIB}/lcg/external/Boost/1.39.0_python2.5/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/packages/geant4/4.9.3.p01/x86_64-slc5-gcc43-opt/geant4.9.3.p01/lib/Linux-g++"
    "${BOSS_ELIB}/packages/CLHEP/2.0.4.5/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/packages/CLHEP/Alist/Alist-00-00-06/x86_64-slc5-gcc43-opt"
    "${BOSS_ELIB}/packages/CLHEP/String/String-00-00-05/x86_64-slc5-gcc43-opt"
    "${BOSS_ELIB}/lcg/external/cernlib/2006a/x86_64-slc5-gcc43-opt/lib"
    # "/usr/X11R6/lib"
    "/usr/lib"
    "${BOSS_ELIB}/lcg/external/lapack/3.1.1/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/lcg/external/blas/20070405/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/lcg/external/castor/2.1.8-10/x86_64-slc5-gcc43-opt/usr/lib64"
    "${BOSS_ELIB}/lcg/external/HepMC/2.03.11/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/lcg/external/HepPDT/2.05.04/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/lcg/external/XercesC/2.8.0/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/lcg/external/mysql/5.0.18/x86_64-slc5-gcc43-opt/lib"
    "${BOSS_ELIB}/lcg/external/mysql/5.0.18/x86_64-slc5-gcc43-opt/lib/mysql"
    "${BOSS_ELIB}/lcg/external/sqlite/3.6.8/x86_64-slc5-gcc43-opt/lib"
)
# DO NOT replace semicolon!
# string(REPLACE ";" " " LIBDIRS "${LIBDIRS}")

# from `cmt show macro_value cppflags`
target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall -Wextra -g -pthread -Wno-deprecated
    -Wno-empty-body -D_GNU_SOURCE -pthread -pipe -ansi -pedantic -W
    -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long
    -march=x86-64 -mtune=x86-64 -pedantic-errors -Og -DEXTEND
    )
# from `cmt show macro_value cpplinkflags`
# and partly from `cmt show macro_value <PACKAGE_NAME>_shlibflags`
target_link_options(${PROJECT_NAME} PUBLIC
    -Wl,-Bdynamic -ldl -Wl,--no-undefined -Wl,--export-dynamic -fPIC -ldl
    -Wl,--no-undefined
    )

foreach(LIBN ${LIBNAMES})
    find_library(TEMPLIB
        NAMES ${LIBN}
        PATHS ${LIBDIRS} ENV LD_LIBRARY_PATH
        NO_DEFAULT_PATH
    )
    if(NOT TEMPLIB)
        message("*** ${LIBN} IS NOT FOUND! ***")
    endif()

    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${TEMPLIB})

    # clear temp variable.
    unset(TEMPLIB CACHE)
endforeach()

#===================================================================<<<
#====================== CMakeLists.txt ends here ======================
