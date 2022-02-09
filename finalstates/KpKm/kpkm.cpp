
#include "kpkm.h"

namespace matthewn{

  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void kpkm::Define(){
    //Set final state detected particles
    //Note if particle is added to final with a valid genID it will be used
    //to determine the correct permutation of the simulated event

    AddParticle("Electron",&_electron,kTRUE,3);
    AddParticle("Proton",&_proton,kTRUE,2);
    AddParticle("Kaonp",&_kaonp,kTRUE,0);
    AddParticle("Kaonm",&_kaonm,kTRUE,1);
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
    _doToTopo["Electron:Proton:Kaonp:Kaonm"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////
      // Adding TLorentzVectors for misidentified particles
      // Invariant and missing masses
      // Calculate possible resonances
      HSLorentzVector missall= _beam + _target - _electron.P4() - _proton.P4()
      -_kaonp.P4()-_kaonm.P4();

        HSLorentzVector invkpkm = _kaonp.P4() + _kaonm.P4();


        HSLorentzVector missp= _beam + _target - _electron.P4() -_kaonp.P4()
        -_kaonm.P4();

        HSLorentzVector misskp= _beam + _target - _electron.P4() - _proton.P4()
        -_kaonm.P4();

        HSLorentzVector misskm= _beam + _target - _electron.P4() - _proton.P4()
        -_kaonp.P4();

        HSLorentzVector missres= _beam + _target - _electron.P4() - _proton.P4();

        HSLorentzVector momentum_exchange= _proton.P4() - _target;

        _kinCalc.SetMesonBaryon(invkpkm,_proton.P4());
        _kinCalc.ElectroCMDecay();

        _kinCalc.SetMesonDecay(_kaonp.P4(), _kaonm.P4());
        _kinCalc.MesonDecayGJ();

        TD->InvKpKm=invkpkm.M();
        TD->MissMassAll2=missall.M2();
        TD->MissMassp=missp.M();
        TD->MissMasskp=misskp.M();
        TD->MissMasskm=misskm.M();
        TD->MissMassRes=missres.M();
        TD->MomentumExchange=momentum_exchange.M2();

        // Putting loose cut on exclusivity to reduce file size
             if(fabs(missall.M2()) > 0.5) return RejectEvent(); //will not process Kinematics

      ///////------------------------------------///////
    };

    /*  _doToTopo["Electron:Proton:Kaonp"]=[&](){
    //TOPOLOGY Define your topology dedendent code in here
    ///////+++++++++++++++++++++++++++++++++++///////
    // Adding TLorentzVectors for misidentified particles
    // Invariant and missing masses
    // Calculate possible resonances
    HSLorentzVector invKpKm = _kaonp.P4() + _kaonm.P4();

    HSLorentzVector missall= _beam + _target - _electron.P4() - _proton.P4()
    -_kaonp.P4()-_kaonm.P4();

    HSLorentzVector missp= _beam + _target - _electron.P4() -_kaonp.P4()
    -_kaonm.P4();

    HSLorentzVector misskp= _beam + _target - _electron.P4() - _proton.P4()
    -_kaonm.P4();

    HSLorentzVector misskm= _beam + _target - _electron.P4() - _proton.P4()
    -_kaonp.P4();

    HSLorentzVector missres= _beam + _target - _electron.P4() - _proton.P4();

    _kinCalc.SetMesonBaryon(invkpkm,_proton.P4());
    _kinCalc.ElectroCMDecay();

    _kinCalc.SetMesonDecay(_kaonp.P4(), _kaonm.P4());
    _kinCalc.MesonDecayGJ();


    TD->InvKpKm=invkpkm.M();
    TD->MissMassAll2=missall.M2();
    TD->MissMassp=missp.M();
    TD->MissMasskp=misskp.M();
    TD->MissMasskm=misskm.M();
    TD->MissMassRes=missres.M();
    // misidentified particles


    ///////------------------------------------///////
  }; */

}


///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
void kpkm::Kinematics(){
  //Define reaction specific kinematic calculations here
  //Assign to tree data TD.var=

  //Use Kinematics to calculate electron variables
  //Note this assumes you called your electron "electron" or "Electron"
  _kinCalc.SetElecsTarget(_beam,_electron.P4(),_target);
  TD->W=_kinCalc.W(); //photon bem energy
  TD->Q2=_kinCalc.Q2();
  TD->Pol=_kinCalc.GammaPol();
  TD->Egamma=_kinCalc.GammaE();

  TD->kaonp_delta_time= _kaonp.DeltaTimeVer();
  TD->kaonm_delta_time= _kaonm.DeltaTimeVer();
  TD->proton_delta_time= _proton.DeltaTimeVer();
  TD->electron_delta_time= _electron.DeltaTimeVer();

  TD->proton_theta = _proton.P4().Theta();
  TD->electron_theta = _electron.P4().Theta();
  TD->kaonm_theta = _kaonm.P4().Theta();
  TD->kaonp_theta = _kaonp.P4().Theta();

  TD->proton_Phi = _proton.P4().Phi();
  TD->electron_Phi = _electron.P4().Phi();
  TD->kaonm_Phi = _kaonm.P4().Phi();
  TD->kaonp_Phi = _kaonp.P4().Phi();

  TD->proton_momentum = _proton.P4().P();
  TD->electron_momentum = _electron.P4().P();
  TD->kaonm_momentum = _kaonm.P4().P();
  TD->kaonp_momentum = _kaonp.P4().P();



  TD->ProdCosThGJ= _kinCalc.CosTheta();
  TD->PolPhi= _kinCalc.Phi();


  TD->CosTh=_kinCalc.CosTheta();
  TD->Phi=_kinCalc.Phi();
}

///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
void kpkm::UserProcess(){
  //Optional additional steps
  //This is called after the Topo function
  //and before the kinematics function
  _counter++;


  //Must call the following to fill Final trees etc.
  //Fill Final data output at the end
  FinalState::UserProcess();

}
}
