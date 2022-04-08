
#include "Scaling_Strangeness.h"

namespace matthewn{

  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void Scaling_Strangeness::Define(){
    //Set final state detected particles
    //Note if particle is added to final with a valid genID it will be used
    //to determine the correct permutation of the simulated event

    AddParticle("Electron",&_electron,kTRUE,-1);
    AddParticle("Kaonp1",&_kaonp1,kTRUE,-1);
    AddParticle("Kaonp2",&_kaonp2,kTRUE,-1);
    AddParticle("Kaonp3",&_kaonp3,kTRUE,-1);
    //AddParticle("Name",particle,true/false you want to write in final vector, genID for linking to generated truth value)
    // AddParticle("PARTICLE",&_PARTICLE,kTRUE,-1);

    //Set final state parents


    //_doToTopo["TOPOLOGY"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////
    ////auto miss= _beam + _target - _electron.P4() - _proton.P4()
    ////  -_pip1.P4()-_pim1.P4();
    ////TD->MissMass=miss.M();
    ////TD->MissMass2=miss.M2();

      ///////------------------------------------///////
    // };

    //Set Possible Topologies
    _doToTopo["Electron:Kaonp1"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////

      // Reconstruct particles
      HSLorentzVector miss1K= _beam + _target - _electron.P4() - _kaonp1.P4();

      TD->Miss1K=miss1K.M();

      ///////------------------------------------///////
    };
    _doToTopo["Electron:Kaonp1:Kaonp2"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////

      // Reconstruct particles
      HSLorentzVector miss2K= _beam + _target - _electron.P4() - _kaonp1.P4()
      - _kaonp2.P4();

      TD->Miss2K=miss2K.M();

      ///////------------------------------------///////
    };
    _doToTopo["Electron:Kaonp1:Kaonp2:Kaonp3"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////

      // Reconstruct particles
      HSLorentzVector miss3K= _beam + _target - _electron.P4() - _kaonp1.P4()
      - _kaonp2.P4() - _kaonp3.P4();

      TD->Miss3K=miss3K.M();

      ///////------------------------------------///////
    };

  }


  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void Scaling_Strangeness::Kinematics(){
    //Define reaction specific kinematic calculations here
    //Assign to tree data TD.var=

    //Use Kinematics to calculate electron variables
    //Note this assumes you called your electron "electron" or "Electron"
    _kinCalc.SetElecsTarget(_beam,_electron.P4(),_target);
    TD->W=_kinCalc.W(); //photon bem energy
    TD->Q2=_kinCalc.Q2();
    TD->Pol=_kinCalc.GammaPol();
    TD->Egamma=_kinCalc.GammaE();

    // Particle kinematics
    // Delta time
    TD->electron_delta_time= _electron.DeltaTimeVer();
    TD->Kaonp_1_delta_time= _kaonp1.DeltaTimeVer();
    TD->Kaonp_2_delta_time= _kaonp2.DeltaTimeVer();
    TD->Kaonp_3_delta_time= _kaonp3.DeltaTimeVer();

    // Momentum
    TD->electron_momentum = _electron.P4().P();
    TD->Kaonp_1_momentum= _kaonp1.P4().P();
    TD->Kaonp_2_momentum= _kaonp2.P4().P();
    TD->Kaonp_3_momentum= _kaonp3.P4().P();

    // Theta
    TD->electron_theta = _electron.P4().Theta();
    TD->Kaonp_1_theta = _kaonp1.P4().Theta();
    TD->Kaonp_2_theta = _kaonp2.P4().Theta();
    TD->Kaonp_3_theta = _kaonp3.P4().Theta();

    // Phi
    TD->electron_Phi = _electron.P4().Phi();
    TD->Kaonp_1_Phi = _kaonp1.P4().Phi();
    TD->Kaonp_2_Phi = _kaonp2.P4().Phi();
    TD->Kaonp_3_Phi = _kaonp3.P4().Phi();

    // cout<<"event_info "<<_eventInfo->_TrigBit<<endl;
    // cout<<"c12 "<<_c12->runconfig()->getTrigger()<<endl;
    // Trigger bit information
    // TD->Trigger = _eventInfo._TrigBit;

    // TD->Trigger_Binary = std::string binary2 = std::bitset<32>(Trigger).to_string();
  }

  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void Scaling_Strangeness::UserProcess(){
    //Optional additional steps
    //This is called after the Topo function
    //and before the kinematics function
    _counter++;


    //Must call the following to fill Final trees etc.
    //Fill Final data output at the end
    FinalState::UserProcess();

  }


}
