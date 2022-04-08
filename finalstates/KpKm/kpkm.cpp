
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
         HSLorentzVector test= _beam + _target - _proton.P4() - _kaonp.P4();
         HSLorentzVector t_four_vector=  _proton.P4() - _target;

         TD->test_miss= test.M();
         TD->t_momentum= t_four_vector.M();

         TD->InvKpKm=invkpkm.M();
         TD->MissMassAll2=missall.M2();
         TD->MissMassp=missp.M();
         TD->MissMasskp=misskp.M();
         TD->MissMasskm=misskm.M();
         TD->MissMassRes=missres.M();
         TD->MomentumExchange=momentum_exchange.M2();

         // Check the MesonEx trigger it. No trigger bit for simulation
         // Either 24 or 25
         TD->MesonExTrig=GetEventInfo()->CLAS12()->checkTriggerBit(25);

         // Putting loose cut on exclusivity to reduce file size
         if(fabs(missall.M2()) > 0.5) return RejectEvent(); //will not process Kinematics


         ///////------------------------------------///////
      };
      _doToTopo["Electron:Kaonp:Kaonm"]=[&](){
         //TOPOLOGY Define your topology dedendent code in here
         ///////+++++++++++++++++++++++++++++++++++///////

         // Adding TLorentzVectors for misidentified particles
         // Invariant and missing masses
         // Calculate possible resonances
         HSLorentzVector invkpkm = _kaonp.P4() + _kaonm.P4();

         HSLorentzVector missp= _beam + _target - _electron.P4() -_kaonp.P4()
         -_kaonm.P4();

         HSLorentzVector missall= _beam + _target - _electron.P4() - missp
         -_kaonp.P4()-_kaonm.P4();

         HSLorentzVector misskp= _beam + _target - _electron.P4() - missp
         -_kaonm.P4();

         HSLorentzVector misskm= _beam + _target - _electron.P4() - missp
         -_kaonp.P4();

         HSLorentzVector missres= _beam + _target - _electron.P4() - _proton.P4();

         HSLorentzVector t_four_vector= missp - _target;


         _kinCalc.SetMesonBaryon(invkpkm,missp);
         _kinCalc.ElectroCMDecay();

         _kinCalc.SetMesonDecay(_kaonp.P4(), _kaonm.P4());
         _kinCalc.MesonDecayGJ();


         TD->InvKpKm=invkpkm.M();
         TD->MissMassp=missp.M();
         TD->MissMassAll2=missall.M2();
         TD->MissMasskp=misskp.M();
         TD->MissMasskm=misskm.M();
         TD->MissMassRes=missres.M();

         // Check the MesonEx trigger it. No trigger bit for simulation
         // Either 24 or 25
         TD->MesonExTrig=GetEventInfo()->CLAS12()->checkTriggerBit(25);

         // Putting loose cut on reconstructed proton to reduce file size
         if(missp.M() < 0.5 || missp.M() > 1.5) return RejectEvent(); //will not process Kinematics



         ///////------------------------------------///////
      };
      _doToTopo["Electron:Proton:Kaonp"]=[&](){
         //TOPOLOGY Define your topology dedendent code in here
         ///////+++++++++++++++++++++++++++++++++++///////

         // Adding TLorentzVectors for misidentified particles
         // Invariant and missing masses
         HSLorentzVector misskm= _beam + _target - _electron.P4() - _proton.P4()
         -_kaonp.P4();

         HSLorentzVector invkpkm = _kaonp.P4() + misskm;

         HSLorentzVector missp= _beam + _target - _electron.P4() -_kaonp.P4()
         - misskm;

         HSLorentzVector misskp= _beam + _target - _electron.P4() - _proton.P4()
         - misskm;

         HSLorentzVector missres= _beam + _target - _electron.P4() - _proton.P4();

         HSLorentzVector momentum_exchange= _proton.P4() - _target;

         _kinCalc.SetMesonBaryon(invkpkm,_proton.P4());
         _kinCalc.ElectroCMDecay();

         _kinCalc.SetMesonDecay(_kaonp.P4(), misskm);
         _kinCalc.MesonDecayGJ();

         HSLorentzVector t_four_vector= _proton.P4() - _target;

         TD->t_momentum= t_four_vector.M();

         TD->InvKpKm=invkpkm.M();
         TD->MissMassp=missp.M();
         TD->MissMasskp=misskp.M();
         TD->MissMasskm=misskm.M();
         TD->MissMassRes=missres.M();
         TD->MomentumExchange=momentum_exchange.M2();

         // Check the MesonEx trigger it. No trigger bit for simulation
         // Either 24 or 25
         TD->MesonExTrig=GetEventInfo()->CLAS12()->checkTriggerBit(25);


         // Putting loose cut on reconstructed k- to reduce file size
         if(misskm.M() < 0.2 || misskm.M() > 0.8) return RejectEvent(); //will not process Kinematics


         ///////------------------------------------///////
      };
      _doToTopo["Electron:Proton:Kaonm"]=[&](){
         //TOPOLOGY Define your topology dedendent code in here
         ///////+++++++++++++++++++++++++++++++++++///////

         // Adding TLorentzVectors for misidentified particles
         // Invariant and missing masses
         HSLorentzVector misskp= _beam + _target - _electron.P4() - _proton.P4()
         -_kaonm.P4();

         HSLorentzVector invkpkm = _kaonm.P4() + misskp;

         HSLorentzVector missp= _beam + _target - _electron.P4() -_kaonm.P4()
         - misskp;

         HSLorentzVector misskm= _beam + _target - _electron.P4() - _proton.P4()
         -misskp;

         HSLorentzVector missres= _beam + _target - _electron.P4() - _proton.P4();

         HSLorentzVector momentum_exchange= _proton.P4() - _target;

         _kinCalc.SetMesonBaryon(invkpkm,_proton.P4());
         _kinCalc.ElectroCMDecay();

         _kinCalc.SetMesonDecay(_kaonm.P4(), misskp);
         _kinCalc.MesonDecayGJ();

         HSLorentzVector t_four_vector= _proton.P4() - _target;

         TD->t_momentum= t_four_vector.M();

         TD->InvKpKm=invkpkm.M();
         TD->MissMassp=missp.M();
         TD->MissMasskp=misskp.M();
         TD->MissMasskm=misskm.M();
         TD->MissMassRes=missres.M();
         TD->MomentumExchange=momentum_exchange.M2();

         // Check the MesonEx trigger it. No trigger bit for simulation
         // Either 24 or 25
         TD->MesonExTrig=GetEventInfo()->CLAS12()->checkTriggerBit(25);


         // Putting loose cut on reconstructed k- to reduce file size
         if(misskp.M() < 0.2 || misskp.M() > 0.8) return RejectEvent(); //will not process Kinematics


         ///////------------------------------------///////
      };

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


      // Particle kinematics
      TD->kaonp_beta= _kaonp.Beta();
      TD->kaonm_beta= _kaonm.Beta();
      TD->proton_beta= _proton.Beta();
      TD->electron_beta= _electron.Beta();

      TD->kaonp_delta_time= _kaonp.DeltaTimeVer();
      TD->kaonm_delta_time= _kaonm.DeltaTimeVer();
      TD->proton_delta_time= _proton.DeltaTimeVer();
      TD->electron_delta_time= _electron.DeltaTimeVer();

      TD->proton_theta = TMath::RadToDeg()*_proton.P4().Theta();
      TD->electron_theta = TMath::RadToDeg()*_electron.P4().Theta();
      TD->kaonm_theta = TMath::RadToDeg()*_kaonm.P4().Theta();
      TD->kaonp_theta = TMath::RadToDeg()*_kaonp.P4().Theta();

      TD->proton_Phi = TMath::RadToDeg()*_proton.P4().Phi();
      TD->electron_Phi = TMath::RadToDeg()*_electron.P4().Phi();
      TD->kaonm_Phi = TMath::RadToDeg()*_kaonm.P4().Phi();
      TD->kaonp_Phi = TMath::RadToDeg()*_kaonp.P4().Phi();

      TD->proton_momentum = _proton.P4().P();
      TD->electron_momentum = _electron.P4().P();
      TD->kaonm_momentum = _kaonm.P4().P();
      TD->kaonp_momentum = _kaonp.P4().P();

      // TD->kaonp_mass= sqrt((pow(kaonp.P4().P(),2) / (pow(kaonp.Beta(),2))) - pow(kaonp.P4().P(),2));
      // TD->kaonm_mass= sqrt((pow(kaonm.P4().P(),2) / (pow(kaonm.Beta(),2))) - pow(kaonm.P4().P(),2));
      // TD->proton_mass= sqrt((pow(proton.P4().P(),2) / (pow(proton.Beta(),2))) - pow(proton.P4().P(),2));
      // TD->electron_mass= sqrt((pow(electron.P4().P(),2) / (pow(electron.Beta(),2))) - pow(electron.P4().P(),2));

      // sqrt((pow(kpkmkaonp_momentum,2) / (pow(kpkmkaonp_beta,2))) - pow(kpkmkaonp_momentum,2))


      // Define decay angles
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
