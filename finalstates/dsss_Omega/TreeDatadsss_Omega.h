#pragma once


#include "BaseOutEvent.h"

#pragma link C++ class mnicol::TreeDatadsss_Omega;

namespace mnicol{

  class TreeDatadsss_Omega : public chanser::BaseOutEvent{

  public:
    TreeDatadsss_Omega(){SetName("dsss_Omega");}
    ~TreeDatadsss_Omega() final =default;
      
    //data member for tree branches below here
    Double_t MissMass=0;
    Double_t MissMass2=0;

    //example of e- kinematics
    //you can remove these if not using
    Double_t W=0;
    Double_t Q2=0;
    Double_t Pol=0;
    Double_t Egamma=0;
  


    ///////////////////////////////////////////////////////////
    //LEAVE THE FOLLOWING FUNCTIONS
    //Function required to set tree branches
    void Branches(TTree* tree) final{
      BaseOutEvent::Branches(tree,Class()->GetListOfDataMembers());
    }
    void Hipo(hipo::ntuple_writer* writer) final{
      BaseOutEvent::Hipo(writer,Class()->GetListOfDataMembers());
    }
      
    ClassDefOverride(TreeDatadsss_Omega,1);
  };
}
