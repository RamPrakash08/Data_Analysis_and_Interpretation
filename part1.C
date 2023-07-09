TH1D* part1(char *tree_fetch){

    TFile *file = new TFile("hist1.root");
    TTree *tree = (TTree*)file->Get(tree_fetch);;
    Int_t entries = tree->GetEntries();

    const Int_t maxTrack = 10000;

    Int_t ntrack ;
    Double_t pid[maxTrack];
    

    tree->SetBranchAddress("pid", &pid);
    tree->SetBranchAddress("ntrack", &ntrack);

     char d[]="de";
    strncat(tree_fetch, d, 2);
    TH1D *h_chg_d = new TH1D(tree_fetch, "Charge Distribution", 100, -30, 30);

    for(Int_t m=0; m<entries; m++)  {
        tree->GetEntry(m);        
	    Int_t net_chg = 0;

        for(int i=0; i<ntrack; i++)  {
            if(pid[i]>0){
                net_chg += 1;
            }
            else if (pid[i]==0)
            {
                continue;
            }
            else //if(pid[i]>0)
            {
                net_chg-=1;
            }
         
        h_chg_d->Fill(net_chg);  
        }
    }

    return h_chg_d;

}

void charge_sym_hist(){

    char tree_1[]="pytree";
    char tree_2[]="pytree2040";
    char tree_3[]="pytree4060";
    char tree_4[]="pytree6080";
    char tree_5[]="pytree80100";
    char tree_6[]="pytree100";

   

    
    TH1D *h1 = chg_sym_h(tree_1);
    TH1D *h2 = chg_sym_h(tree_2);
    TH1D *h3 = chg_sym_h(tree_3);
    TH1D *h4 = chg_sym_h(tree_4);
    TH1D *h5 = chg_sym_h(tree_5);
    TH1D *h6 = chg_sym_h(tree_6);

     TFile *file_new = new TFile("charge_asymmetry_plots.root", "recreate");
    
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    h5->Write();
    h6->Write();
    

}