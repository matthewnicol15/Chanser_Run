//////////////////////////////////////////////////////////////
///
///Class:		Scaling_Strangeness
///Description:
///
#pragma once


#include "CLAS12FinalState.h"
#include "CLAS12Particle.h"

#include "TreeDataScaling_Strangeness.h"


namespace matthewn{

  using Particle=chanser::CLAS12Particle;

  class Scaling_Strangeness : public chanser::CLAS12FinalState{


  public :
    Scaling_Strangeness()=default;

   TString GetUSER() final {return _USER;};

    //create an instance of the class
    static std::unique_ptr<Scaling_Strangeness> Make(TString ch,TString inc) {
      return std::unique_ptr<Scaling_Strangeness>{new Scaling_Strangeness{ch,inc}};
    }
    //create an instance of the treedata, should be used to init unique_ptr
    chanser::base_outevt_uptr TreeDataFactory() final {
      return chanser::base_outevt_uptr{new TreeDataScaling_Strangeness{}};
    }
    void SetOutEvent(BaseOutEvent* out) final{
      TD=static_cast<TreeDataScaling_Strangeness*>(out);
    }

    ~Scaling_Strangeness() final =default;

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
    //using Scaling_Strangeness::Make(...)
    //auto fs = matthewn::Scaling_Strangeness::Make("NONE","ALL");
  Scaling_Strangeness(TString ch,TString inc) : chanser::CLAS12FinalState(std::move(ch),std::move(inc)){
      //Give object class name - namespace
      //Used for compiling and loading
      SetName(chanser::Archive::BareClassName(ClassName()));
      Define();
    }

    //Final Particles Detected
    Particle   _electron = Particle{"e-"};//!
    Particle   _kaonp1 = Particle{"K+"};//!
    Particle   _kaonp2 = Particle{"K+"};//!
    Particle   _kaonp3 = Particle{"K+"};//!
    //chanser::CLAS12Particle _PARTICLE=BaseParticle("PDG");//!

    //Final Parents


    //Initial state
    HSLorentzVector _beam{0,0,10.6,10.6};//!
    HSLorentzVector _target{0,0,0,0.938272};//!


    //Tree Output Data
    TreeDataScaling_Strangeness* TD{nullptr};//!;



    const TString _USER="matthewn";
    ClassDefOverride(matthewn::Scaling_Strangeness,1); //class Scaling_Strangeness
  }; //end Scaling_Strangeness

}
