#include "HttStylesNew.cc"
#include "CMS_lumi.C"
// era ->
// 2016postVFP
// 2016preVFP
// 2017
// 2018
//
// EtaBin ->
// EtaLt0p9
// Eta0p9to1p2
// Eta1p2to2p1
// EtaGt2p1
//
// trigger = true (trigger efficiencies)
//           false (ID/Iso efficiencies)
void PlotMuonEff(TString era = "2018",
		 TString EtaBin = "Eta0p9to1p2",
		 bool trigger = true) {

  int nMax = 15;

  if (era=="2018"||
      era=="2017"||
      era=="2016postVFP"||
      era=="2016preVFP") 
    std::cout << "Era -> " << era << std::endl;

  if (EtaBin=="EtaLt0p9"||
      EtaBin=="Eta0p9to1p2"||
      EtaBin=="Eta1p2to2p1"||
      EtaBin=="EtaGt2p1") 
    std::cout << "Eta bin -> " << EtaBin << std::endl;
  else {
    std::cout << "Unknown eta bin specified " << EtaBin << std::endl;
    return;
  }


  SetStyle();


  map<TString, TString> etaBinMap = {
    {"EtaLt0p9","|#eta|<0.9"},
    {"Eta0p9to1p2","0.9<|#eta|<1.2"},
    {"Eta1p2to2p1","1.2<|#eta|<2.1"},
    {"EtaGt2p1","2.1<|#eta|<2.4"}
  };
  

  TString name("Id/Iso");
  TString FileName = "MuonID/UL"+era+"/Muon_RunUL"+era+"_IdIso_AZh_IsoLt0p15_IdLoose.root";
  if (trigger) {
    name = "Mu27";
    FileName = "MuonTrigger/UL"+era+"/Muon_RunUL"+era+"_IsoMu27.root";
    if (era.Contains("2016")) {
      FileName = "MuonTrigger/UL"+era+"/Muon_RunUL"+era+"_IsoMu24orIsoTkMu24.root";
      name = "Mu24";
    }
  }

  TString Header = name+", "+etaBinMap[EtaBin];

  TFile * file = new TFile(FileName);

  TString histNameData = "ZMass"+EtaBin+"_Data";
  TString histNameMC = "ZMass"+EtaBin+"_MC";

  TGraphAsymmErrors * effData = (TGraphAsymmErrors*)file->Get(histNameData);
  TGraphAsymmErrors * effMC = (TGraphAsymmErrors*)file->Get(histNameMC);

  effData->SetLineColor(2);
  effData->SetMarkerColor(2);
  effData->SetMarkerSize(1.5);
  effData->SetMarkerStyle(20);

  effMC->SetLineColor(4);
  effMC->SetMarkerColor(4);
  effMC->SetMarkerSize(1.5);
  effMC->SetMarkerStyle(21);

  int nBins = effData->GetN();
  float bins[100];
  std::cout << "nBins = " << nBins << std::endl;
  std::cout << "efficiencies -> " << std::endl;
  for (int iB=0; iB<nBins; ++iB) {
    bins[iB] = effData->GetX()[iB] - effData->GetErrorX(iB);
    float lower = bins[iB];
    float upper = effData->GetX()[iB] + effData->GetErrorX(iB);
    printf("[%2i,%3i] : %5.3f - %5.3f\n",int(lower),int(upper),effData->GetY()[iB],effMC->GetY()[iB]);

  }
  bins[nBins] = effData->GetX()[nBins-1] + effData->GetErrorX(nBins-1);
  double xmin = 10;
  double xmax = 100;
  if (trigger) { 
    xmin = 26;
    xmax = 120;
  }

  TH1D * SF = new TH1D("SF","",nBins,bins);
  SF->GetXaxis()->SetTitle("muon p_{T} [GeV]");
  SF->SetMarkerColor(1);
  SF->SetMarkerStyle(20);
  SF->SetMarkerSize(1.2);
  SF->SetLineColor(1);
  SF->GetYaxis()->SetRangeUser(0.901,1.099);
  SF->GetYaxis()->SetNdivisions(505);
  SF->GetXaxis()->SetLabelFont(42);
  SF->GetXaxis()->SetLabelOffset(0.04);
  SF->GetXaxis()->SetLabelSize(0.14);
  SF->GetXaxis()->SetTitleSize(0.13);
  SF->GetXaxis()->SetTitleOffset(1.2);
  SF->GetYaxis()->SetTitle("SF");
  SF->GetYaxis()->SetLabelFont(42);
  SF->GetYaxis()->SetLabelOffset(0.015);
  SF->GetYaxis()->SetLabelSize(0.13);
  SF->GetYaxis()->SetTitleSize(0.14);
  SF->GetYaxis()->SetTitleOffset(0.5);
  SF->GetXaxis()->SetTickLength(0.07);
  SF->GetYaxis()->SetTickLength(0.04);
  SF->GetYaxis()->SetLabelOffset(0.01);

  SF->GetXaxis()->SetRangeUser(xmin,xmax-0.01);
    
  std::cout << std::endl;
  std::cout << "Scale factors -> " << std::endl;
  for (int iB=0; iB<nBins; ++iB) {
    float num = effData->GetY()[iB];
    float eNum = effData->GetErrorY(iB);
    float den = effMC->GetY()[iB];    
    float sf = 0;
    float sfE = 0; 
    if (den>0) { 
      sf = num/den; 
      sfE = eNum/den;
    }
    SF->SetBinContent(iB+1,sf);
    SF->SetBinError(iB+1,sfE);
    float lower = SF->GetBinLowEdge(iB+1);
    float upper = SF->GetBinLowEdge(iB+2);
    printf("[%2i,%3i] : %5.3f +/- %5.3f\n",int(lower),int(upper),sf,sfE);
  }
  std::cout << std::endl;

  TH2F * frame = new TH2F("frame","",2,xmin,xmax,2,0.,1.2);
  frame->GetXaxis()->SetTitle();
  frame->GetYaxis()->SetTitle("efficiency");
  frame->GetYaxis()->SetTitleOffset(1.2);
  frame->GetXaxis()->SetLabelSize(0);

  TCanvas * canv = MakeCanvas("canv","",600,700);
  TPad *upper = new TPad("upper", "pad",0,0.31,1,1);
  upper->Draw();
  upper->cd();
  upper->SetFillColor(0);
  upper->SetBorderMode(0);
  upper->SetBorderSize(10);
  upper->SetTickx(1);
  upper->SetTicky(1);
  upper->SetLeftMargin(0.17);
  upper->SetRightMargin(0.05);
  upper->SetBottomMargin(0.02);
  upper->SetFrameFillStyle(0);
  upper->SetFrameLineStyle(0);
  upper->SetFrameLineWidth(2);
  upper->SetFrameBorderMode(0);
  upper->SetFrameBorderSize(10);
  upper->SetFrameFillStyle(0);
  upper->SetFrameLineStyle(0);
  upper->SetFrameLineWidth(2);
  upper->SetFrameBorderMode(0);
  upper->SetFrameBorderSize(10);

  //  upper->SetGridx();
  //  upper->SetGridy();

  frame->Draw();
  effMC->Draw("PEsame");
  effData->Draw("PEsame");
  TLegend * legend = new TLegend(0.4,0.17,0.94,0.40);
  SetLegendStyle(legend);
  legend->SetHeader(Header);
  legend->SetTextSize(0.06);
  legend->AddEntry(effData,"Data","lp");
  legend->AddEntry(effMC,"MC (Z#rightarrow#mu#mu)","lp");
  legend->Draw();

  if (era=="2016preVFP") lumi_13TeV = "2016 preVFP, 19.5 fb^{-1}";
  if (era=="2016postVFP") lumi_13TeV = "2016 postVFP, 16.8 fb^{-1}";
  if (era=="2017") lumi_13TeV = "2017, 41.5 fb^{-1}";
  if (era=="2018") lumi_13TeV = "2018, 59.8 fb^{-1}";

  writeExtraText = true;
  extraText   = "Internal";
  CMS_lumi(upper,4,33); 


  upper->Draw("SAME");
  upper->RedrawAxis();
  upper->Modified();
  upper->Update();
  canv->cd();

  TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
  lower->Draw();
  lower->cd();
  lower->SetFillColor(0);
  lower->SetBorderMode(0);
  lower->SetBorderSize(10);
  lower->SetGridy();
  lower->SetTickx(1);
  lower->SetTicky(1);
  lower->SetLeftMargin(0.17);
  lower->SetRightMargin(0.05);
  lower->SetTopMargin(0.026);
  lower->SetBottomMargin(0.35);
  lower->SetFrameFillStyle(0);
  lower->SetFrameLineStyle(0);
  lower->SetFrameLineWidth(2);
  lower->SetFrameBorderMode(0);
  lower->SetFrameBorderSize(10);
  lower->SetFrameFillStyle(0);
  lower->SetFrameLineStyle(0);
  lower->SetFrameLineWidth(2);
  lower->SetFrameBorderMode(0);
  lower->SetFrameBorderSize(10);
  SF->Draw("e1");

  lower->Modified();
  lower->RedrawAxis();
  canv->cd();
  canv->SetSelected(canv);
  canv->Update();
  if (trigger)
    canv->Print("Muon_trigger_"+EtaBin+"_"+era+".png");
  else
    canv->Print("Muon_ID_"+EtaBin+"_"+era+".png");

}
