The fake rate root file contains sevarel histograms plotting the fake rate as a function of lepton pT:

**Jet to electron/muon/tauh fake rate root files:**

"PrefitFR_barrel" and "PrefitFR_endcap" are the fake rates obtained by simple prompt subtraction without maximum likelyhood fitting.
"PostfitFR_barrel" and "PostfitFR_endcap" are the fake rates obtained by performing maximum likelyhood fitting and then subtracting data with prompt.
"JetToEle(Mu,Tau)Pre(Post)fit" are the corresponding 2D histogram combined both barrel and endcap regions. 

Instead of binning by barrel and endcap, the faka rate for jet to hadronic tau are binned as functions of reconstructed decay mode.

![JetTauFR_Medium_Tight_VLoose_Prefit_2016](https://user-images.githubusercontent.com/8279060/164252392-6c737249-b296-4aa9-85f7-7aadf5027b54.png)


![JetTauFR_Medium_VLoose_Tight_Postfit_2016](https://user-images.githubusercontent.com/8279060/164252277-43c992c7-8553-436d-82eb-f9e663dbf3dd.png)

The fake rates as function could aslo be fitting by a numerical polynomial fit. And the systematics could be also determined from the fit.
"POL2FitFR_Central_Barrel(Endcap)" returns the value of the fit, while "POL2FitFR_Uncert68(95)_Barrel" returns the 1(2) sigma error.

![FakeRateFit_JetToMu_Loose_Iso0p15_endcap_2018.pdf](https://github.com/wywdiablo/AZhCorrections/files/8522260/FakeRateFit_JetToMu_Loose_Iso0p15_endcap_2018.pdf)

![FakeRateFit_JetToTau_Medium_VLoose_Tight_DM10_2018.pdf](https://github.com/wywdiablo/AZhCorrections/files/8522274/FakeRateFit_JetToTau_Medium_VLoose_Tight_DM10_2018.pdf)


It is worth to note that in the actual analysis, if the pT of fakes are greater than the pT of the last bin of unfitted fake rate, the retrieving of fake rates from the fitted function should only get the fake rate from function using the center x value of the last binned fake rate, because the fit containing no information after that pT value, only extrapolation is being done there.
