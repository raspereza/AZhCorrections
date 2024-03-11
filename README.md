# AZhCorrections
This repo stored the corrections used for the AZh to (ll tau tau analysis

## Plotting muon efficiencies

Muon efficiencies can be plotted with RooT macro [PlotMuonEff.C](https://github.com/raspereza/AZhCorrections/blob/master/PlotMuonEff.C). The input arguments of the macro are explained below:

```
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
```

## Plotting electron efficiencise

Electron efficiencies are plotted with macro [PlotElectronEff.C](https://github.com/raspereza/AZhCorrections/blob/master/PlotElectronEff.C). The input arguments for the macro are:

```
// era ->
// 2016postVFP
// 2016preVFP
// 2017
// 2018
//
// EtaBin ->
// EtaLt1p0
// Eta1p0to1p48
// Eta1p48to1p65
// Eta1p65to2p1
// EtaGt2p1
//
// trigger = true (trigger efficiencies)
//           false (ID/Iso efficiencies)
void PlotElectronEff(TString era = "2018",
		 TString EtaBin = "EtaLt1p0",
		 bool trigger = false) {
```
