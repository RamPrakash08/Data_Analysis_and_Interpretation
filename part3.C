void part3()
{
  TFile *f=new TFile("hist1.root");
  TTree *tree = (TTree*)f->Get("pytree100"); // use the required tree here
  Int_t entries = tree->GetEntries();
  Int_t n_part_plus = 0; Int_t n_part_minus = 0; Int_t n_net; Int_t ntrks;

 const Int_t maxTrack=100000;
   
 Int_t ntrack = 0;
  Double_t pid[maxTrack];
   Double_t pT[maxTrack];
  Double_t eta[maxTrack];
  Double_t rap[maxTrack];
  Double_t phi[maxTrack];
  Double_t net_charge[maxTrack];
  Int_t x=0;
  Int_t y=0;

  tree->SetBranchAddress("pid",&pid);
  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);
 


  TH1D *histo_mult = new TH1D("histo_mult","multiplicity",100,-1.0,350.0);
  TH1D *histo_rap = new TH1D("histo_rap","Rapidity",100,-30.0,30.0);
  TH1D *histo_net_chg = new TH1D("hcharge2040", "Charge asymmetry plot", 100, -30.0, 30.0);
  TH1D *histo_mult_sym = new TH1D("chargesymphi", "multiplicity distribution 2040", 10, 20.0, 40.0);
  TH1D *histo_mult_asym = new TH1D("chargeasymphi", "multiplicity distribution 2040", 10, 20.0, 40.0);
  TH1D *histo_n_net = new TH1D("histo_n_net", "n_net", 50, -50, 50);
  TH1D *histo_sym_pT = new TH1D("histo_sym_pT","pT Distribution Symmetric & Asymmetric (100+ multiplicity)",125, 0, 7);
  TH1D *histo_asym_pT = new TH1D("histo_asym_pT", "pT Distribution Symmetric & Asymmetric (100+ multiplicity)", 125, 0, 7);
  TH1D *histo_sym_eta = new TH1D("histo_sym_eta", "eta Distribution Symmetric & Asymmetric (100+ multiplicity)", 125, -3, 3);
  TH1D *histo_asym_eta = new TH1D("histo_asym_eta", "eta Distribution Symmetric & Asymmetric (100+ multiplicity)", 125, -3, 3);
  TH1D *histo_sym_phi = new TH1D("histo_sym_phi", "phi_distribution-symm_and_asymm", 100, -5, 5);
  TH1D *histo_asym_phi = new TH1D("h_asymm_phhi", "phi_distribution-symm_and_asymm", 100, -5, 5); 


  for(Int_t m=0; m<entries; m++)  {  // Event loop starts here
    tree->GetEntry(m);

      ntrks = ntrack;
      histo_mult->Fill(ntrks);


      for(int i=0; i<ntrks; i++) { //track loop is here


     Double_t pid1 = pid[i];
     if (pid1>0){ n_part_plus += 1;
      }
     else if (pid1<0){ n_part_minus -= 1;
	 }
     Double_t eta1=eta[i];
     histo_rap->Fill(eta1);


   }
     net_charge[m] = n_part_plus - n_part_minus;

	Int_t n_net = net_charge[m]; // net charge is n_net
     if (net_charge[m]>-1 and net_charge[m]<1){
       histo_mult_sym->Fill(ntrack);
			      }
		       else {
			 histo_mult_asym->Fill(ntrack);
		       }

     histo_net_chg->Fill(net_charge[m]);

		       n_part_plus=0; //reset plus charge total 
		       n_part_minus=0; //reset minus charge total
	

     
     if ((n_net<=5) && (n_net>=-5)){
       for (int i=0; i<ntrks; i++){// track loop is here

     Double_t symm_pT1 = pT[i];
     histo_sym_pT->Fill(symm_pT1);
     }

   }
     if ((n_net>5) || (n_net<-5)){
       for (int i=0; i<ntrks; i++) { //track loop is here
      
	 double_t asymm_pT1 = pT[i];
         histo_asym_pT->Fill(asymm_pT1);
     }
   }

     if ((n_net<=18) && (n_net>=-18)){
       for (int i=0; i<ntrks; i++){ //track loop is here

	 Double_t symm_eta1 = eta[i];
         histo_sym_eta->Fill(symm_eta1);
     }
    }

    if ((n_net>18) || (n_net<-18)){
       for (int i=0; i<ntrks; i++){ //track loop is here

	 Double_t asymm_eta1 = eta[i];
         histo_asym_eta->Fill(asymm_eta1);
     }
    }

     if ((n_net<=5) && (n_net>=-5)){
       for (int i=0; i<ntrks; i++){ //track loop is here

	 Double_t symm_phi1 = phi[i];
         histo_sym_phi->Fill(symm_phi1);
       }
     }

     if ((n_net>5) || (n_net<-5)){
       for (int i=0; i<ntrks; i++){ //track loop is here

	 Double_t asymm_phi1 = phi[i];
         histo_asym_phi->Fill(asymm_phi1);
       }
     }
}


     // histo_n_net->Draw();
     histo_sym_pT->SetLineColor(2);
     histo_asym_pT->SetLineColor(4);
     //histo_sym_eta->SetLineColor(2);
     //histo_asym_eta->SetLineColor(4);
     //histo_sym_phi->SetLineColor(2);
     //histo_asym_phi->SetLineColor(4);
  histo_asym_pT->Draw();
  histo_sym_pT->Draw("same");
histo_sym_pT->GetYaxis()->SetRange(0,10000000);
histo_asym_pT->GetYaxis()->SetRange(0,10000000);
  //histo_asym_eta->Draw();
  //histo_sym_eta->Draw("same");
  // histo_sym_phi->Draw();
  //  histo_asym_phi->Draw("same");
  //histo_rap->Draw();
  //histo_mult->Draw();

  //Uncomment different lines and get the graphs
}

