/*=========================================================================
                                                                                
Program:   clitk
Language:  C++
                                                                                
Copyright (c) CREATIS (Centre de Recherche et d'Applications en Traitement de
l'Image). All rights reserved. See Doc/License.txt or
http://www.creatis.insa-lyon.fr/Public/Gdcm/License.html for details.
                                                                                
This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.
                                                                             
=========================================================================*/

#ifndef CLITKIOCOMMON_CXX
#define CLITKIOCOMMON_CXX

/**
   =================================================
   * @file   clitkIOCommon.cxx
   * @author David Sarrut <david.sarrut@creatis.insa-lyon.fr>
   * @date   18 May 2006 11:42:37
   * 
   * @brief  
   * 
   * 
   =================================================*/

// clitk include
#include "clitkImageCommon.h"
#include <cstdlib>

//====================================================================
// Open a file for reading
void clitk::openFileForReading(std::ifstream & is, const std::string & filename) {
  is.open(filename.c_str(), std::ios::in);
  if ( is.fail() ) {
    itkGenericExceptionMacro(<< "Could not open file (for reading): " << filename);
  }
}
//====================================================================
  
//====================================================================
// Open a file for writing
void clitk::openFileForWriting(std::ofstream & os, const std::string & filename)  {
  os.open(filename.c_str(), std::ios::out);
  if ( os.fail() ) {
    itkGenericExceptionMacro(<< "Could not open file (for writing): " << filename);
  }
}
//====================================================================

//====================================================================
// Read a dicom header  
gdcm::File * clitk::readDicomHeader(const std::string & filename, 
				    const bool verbose) {
  if (verbose) {
    std::cout << "Reading DICOM <" << filename << ">" << std::endl;
  }
  gdcm::File *header = new gdcm::File();
  header->SetFileName(filename);
  header->SetMaxSizeLoadEntry(16384); // required ?
  header->Load();
  return header;
}
//====================================================================

//====================================================================
itk::ImageIOBase::Pointer clitk::readImageHeader(const std::string & filename, bool exit_on_error) {
  itk::ImageIOBase::Pointer reader =
    itk::ImageIOFactory::CreateImageIO(filename.c_str(), itk::ImageIOFactory::ReadMode);
  if (!reader) 
      if (exit_on_error) //default behavior for tools who don't handle the problem
      {
          std::cerr "Error reading file " << filename << ", exiting immediately" << std::endl;
          std::exit(-1);
      }
      else
          return NULL;
  reader->SetFileName(filename);
  reader->ReadImageInformation();
  return reader;
}
//====================================================================

//====================================================================
void clitk::printImageHeader(itk::ImageIOBase::Pointer header, std::ostream & os, const int level) {
  unsigned int dim = header->GetNumberOfDimensions();
  std::string pixelTypeName = header->GetComponentTypeAsString(header->GetComponentType());
  std::vector<int> inputSize;
  std::vector<double> inputSpacing;
  inputSize.resize(dim);
  inputSpacing.resize(dim);
  for(unsigned int i=0; i<dim; i++) {
    inputSpacing[i] = header->GetSpacing(i);
    inputSize[i] = header->GetDimensions(i);
  }
  int pixelSize = 
    clitk::GetTypeSizeFromString(header->GetComponentTypeAsString(header->GetComponentType()));
  unsigned int nbOfComponents = header->GetNumberOfComponents();
  if (level == 0) {
    os << dim << "D ";
    if (nbOfComponents !=1) os << nbOfComponents << "x" << pixelTypeName;
    else os << pixelTypeName;
    os << " ";
    for(unsigned int i=0; i< dim-1; i++)
      os << inputSize[i] << "x";
    os << inputSize[dim-1]
       << "  ";
    for(unsigned int i=0; i< dim-1; i++)
      os << inputSpacing[i] << "x";
    os << inputSpacing[dim-1];
  }
  else {
    os << "Dim       = " << dim << "D" << std::endl;
    os << "PixelType = " << pixelTypeName << std::endl;
    if (nbOfComponents > 1)
      os << "Vector    = " << nbOfComponents << std::endl;
    os << "Size      = ";
    for(unsigned int i=0; i< dim; i++) {
      os << inputSize[i] << " ";
    }
    os << std::endl;
    os << "Spacing   = ";
    for(unsigned int i=0; i< dim; i++) {
      os << inputSpacing[i] << " ";
    }
    os << std::endl;
    if (level > 1) {
      os << "# voxels  = " << header->GetImageSizeInPixels() << std::endl;
      os << "Size (mm) = ";
      for(unsigned int i=0; i< dim; i++) {
 	os << inputSize[i]*inputSpacing[i] << " ";
      }
      os << "mm" << std::endl;
      os << "Volume    = ";
      double vol=1.0;
      for(unsigned int i=0; i< dim; i++) {
 	vol *= inputSize[i]*inputSpacing[i]/10.0;
      }
      os << vol << " cc" << std::endl;
      int mem = header->GetImageSizeInPixels()*pixelSize*nbOfComponents;
      double memKb = (double)mem/1024.0;
      double memMb = (double)mem/1024.0/1024.0;
      double memGb = (double)mem/1024.0/1024.0/1024.0;
      if (lrint(memKb) <= 0)
 	os << "Memory    = " << mem << " bytes" << std::endl;
      else {
 	if (lrint(memMb) <= 0)
 	  os << "Memory    = " << memKb << " Kb (" << mem << " bytes)" << std::endl;
 	else {
 	  if (lrint(memGb) <= 0)
 	    os << "Memory    = " << memMb << " Mb (" << mem << " bytes)" << std::endl;
 	  else 
 	    os << "Memory     = " << memGb << " Gb (" << mem << " bytes)" << std::endl;
 	}
      }
    }
  }
}
//====================================================================

#endif /* end #define CLITKIO_CXX */
