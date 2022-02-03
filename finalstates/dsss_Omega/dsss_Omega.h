//////////////////////////////////////////////////////////////
///
///Class:		dsss_Omega
///Description:
///
#pragma once


#include "CLAS12FinalState.h"
#include "CLAS12Particle.h"

#include "TreeDatadsss_Omega.h"


namespace mnicol{

  using Particle=chanser::CLAS12Particle;

  class dsss_Omega : public chanser::CLAS12FinalState{

       
  public :
    dsss_Omega()=default;
      
   TString GetUSER() final {return _USER;};
 
    //create an instance of the class
    static std::unique_ptr<dsss_Omega> Make(TString ch,TString inc) {
      return std::unique_ptr<dsss_Omega>{new dsss_Omega{ch,inc}};
    }
    //create an instance of the treedata, should be used to init unique_ptr
    chanser::base_outevt_uptr TreeDataFactory() final {
      return chanser::base_outevt_uptr{new TreeDatadsss_Omega{}};
    }
    void SetOutEvent(BaseOutEvent* out) final{
      TD=static_cast<TreeDatadsss_Omega*>(out);
    }
  
    ~dsss_Omega() final =default;

    void Define() final;
      
    BaseOutEvent* GetOutEvent() noexcept final{return TD;}
    
    void DerivedChangeRun() final {
      //If databases are implemented you can
      //set the beam energy here
      /*      auto ebeam=GetRunInfo()->_BeamEnergy;
      auto mele = 0.00051099891;
      std::cout<<"Change beam energy to :"<<ebeam<<std::endl;
      _beam.SetXYZT(0,0,ebeam,TMath::Sqrt(ebeam*ebeam + mele*mele));
      */    
    }  
  protected :
    void Kinematics() final;
    void UserProcess() final;
      
      
   
  private:
    //constructor private so only create unique_ptr
    //using dsss_Omega::Make(...)
    //auto fs = mnicol::dsss_Omega::Make("NONE","ALL");
  dsss_Omega(TString ch,TString inc) : chanser::CLAS12FinalState(std::move(ch),std::move(inc)){
      //Give object class name - namespace
      //Used for compiling and loading
      SetName(chanser::Archive::BareClassName(ClassName()));
      Define();
    }

    //Final Particles Detected
    Particle   _electron = Particle{"e-"};//!
    Particle   _proton = Particle{"proton"};//!
    Particle   _pim1 = Particle{"pi-"};//!
    Particle   _pim2 = Particle{"pi-"};//!
    Particle   _kaonp1 = Particle{"k+"};//!
    Particle   _kaonp2 = Particle{"k+"};//!
    Particle   _kaonp3 = Particle{"k+"};//!
    //chanser::CLAS12Particle _PARTICLE=BaseParticle("PDG");//!
    
    //Final Parents
    Particle _lambda = Particle{"Lambda0"};//!
    Particle _omega = Particle{"Omega-"};//!


    //Initial state
    HSLorentzVector _beam{0,0,10.6,10.6};//!
    HSLorentzVector _target{0,0,0,0.938272};//!


    //Tree Output Data
    TreeDatadsss_Omega* TD{nullptr};//!;

   
    
    const TString _USER="mnicol";
    ClassDefOverride(mnicol::dsss_Omega,1); //class dsss_Omega
  }; //end dsss_Omega
  
}
