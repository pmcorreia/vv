/*-------------------------------------------------------------------------
                                                                                
Program:   clitk
Language:  C++
                                                                                
Copyright (c) CREATIS (Centre de Recherche et d'Applications en Traitement de
l'Image). All rights reserved. See Doc/License.txt or
http://www.creatis.insa-lyon.fr/Public/Gdcm/License.html for details.
                                                                                
This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.
                                                                             
-------------------------------------------------------------------------*/

/**
   -------------------------------------------------
   * @file   clitkDicomInfo.cxx
   * @author Laurent ZAGNI <laurent.zagni@insa-lyon.fr>
   * @date   27 Jul 2006
   -------------------------------------------------*/

// clitk includes
#include "clitkDicomInfo_ggo.h"
#include "clitkCommon.h"

// itk (gdcm) include
#include "gdcmFile.h"

//--------------------------------------------------------------------
int main(int argc, char * argv[]) {

  // init command line
  GGO(clitkDicomInfo, args_info);

  // check arg
  if (args_info.inputs_num == 0) return 0;

  // Loop files
  for(unsigned int i=0; i<args_info.inputs_num; i++) {
    gdcm::File *header = new gdcm::File();
    header->SetFileName(args_info.inputs[i]);
    header->SetMaxSizeLoadEntry(16384);
    header->Load();
    header->Print();
  }

  // this is the end my friend  
  return 0;
}
//--------------------------------------------------------------------
