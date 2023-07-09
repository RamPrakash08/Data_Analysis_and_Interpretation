void part2(){

    TCanvas *Canv1 = new TCanvas("Canv1","Canv1",500,500);
    Canv1->SetGrid();
   
    TFile *file = new TFile("hist1.root");
    TTree *tree = (TTree*)file->Get("pytree80100");
    Int_t entries = tree->GetEntries();

    const Int_t maxtrck = 10000;

    Int_t ntrack ;
    
    Double_t pid[maxtrck];

    Double_t pT[maxtrck];

    Double_t eta[maxtrck];

    Double_t rap[maxtrck];

    Double_t phi[maxtrck];
    

    tree->SetBranchAddress("pid", &pid);
    tree->SetBranchAddress("ntrack", &ntrack);
    tree->SetBranchAddress("phi",&phi);
    tree->SetBranchAddress("pT",&pT);
    tree->SetBranchAddress("eta",&eta);
    tree->SetBranchAddress("rap", &rap);

    TH1D *histo_chg = new TH1D("histo_chg", "Charge Distribution", 125, -200, 200);

    TH1D *histo_mult = new TH1D("hmult","multiplicity",125,0.0,150.0);
    TH1D *histo_phi = new TH1D("hphi","Phi",125,-4.0,4.0);
    TH1D* histo_rap = new TH1D("hrap", "Rapidity", 125, -6.0, 6.0);
    TH1D* histo_eta = new TH1D("heta", "Eta", 125, -4.0, 4.0);
    TH1F* histo_pT = new TH1F("hpT", "Transverse Momentum", 125, 0.2, 3);
    
    TH1D *histo_mult_asy = new TH1D("hmult","multiplicity",125,0.0,150.0);
    TH1D *histo_phi_asy = new TH1D("hphi","Phi",125,-4.0,4.0);
    TH1D* histo_rap_asy = new TH1D("hrap", "Rapidity", 125, -6.0, 6.0);
    TH1D* histo_eta_asy = new TH1D("heta", "Eta", 100, -4.0, 4.0);
    TH1F* histo_pT_asy = new TH1F("hpT", "Transverse Momentum", 100, 0.2, 3);


    for(Int_t m=0; m<entries; m++)  {
        tree->GetEntry(m);        
	    Int_t net_chg = 0;

        for(int i=0; i<ntrack; i++)  {
            if(pid[i]>0){
                net_chg += 1;
            }
           
            else{
                net_chg-=1;
                
            }
         
        histo_chg->Fill(net_chg);  

        if(net_chg<10 && net_chg>-10){

            for(int j=0; j<ntrack; j++) { //track loop is here


            Double_t eta1 = eta[j];

            Double_t phi1 = phi[j];

            Double_t rap1 = rap[j];

            Float_t pT1 = pT[j];

            histo_eta->Fill(eta1);

            histo_phi->Fill(phi1);

            histo_pT->Fill(pT1);

            histo_rap->Fill(rap1);

            histo_mult->Fill(ntrack);
        }

        }
        else {

            for(int j=0; j<ntrack; j++) { //track loop is here
            
            Double_t eta1 = eta[j];

            Double_t phi1 = phi[j];

            Double_t rap1 = rap[j];

            Float_t pT1 = pT[j];

            histo_eta_asy->Fill(eta1);

            histo_phi_asy->Fill(phi1);

            histo_pT_asy->Fill(pT1);

            histo_rap_asy->Fill(rap1);

            histo_mult_asy->Fill(ntrack);
        }

          
        }
    
    }
    }

    // Uncomment differnt lines below and get all the graphs
    histo_mult->SetLineColor(2);
    histo_mult->SetLineColor(4);
    //histo_pT->Draw();
    //histo_pT_asy->Draw("same");
    //histo_phi->Draw();
    //histo_phi_asy->Draw("same")
    //histo_eta->Draw();
    //histo_eta_asy->Draw("same")
    histo_mult->Draw();
    histo_mult_asy->Draw("same");
    //histo_rap->Draw();
    //histo_rap_asy->Draw("same")
    //histo_chg->Draw();
}

