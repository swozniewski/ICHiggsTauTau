#ifndef HiggsTauTau_Phys14Plots_h
#define HiggsTauTau_Phys14Plots_h

#include "Core/interface/TreeEvent.h"
#include "Core/interface/ModuleBase.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "TH1F.h"
#include "TH2F.h"

#include <string>

namespace ic {

struct EfficiencyPlot1D {
  TH1F* all;
  TH1F* pass;

  EfficiencyPlot1D() {
    all = nullptr;
    pass = nullptr;
  }

  void Fill(double val, bool passes) {
    all->Fill(val);
    if (passes) pass->Fill(val);
  }

  EfficiencyPlot1D(TFileDirectory *dir, std::string const &name, unsigned nbins,
                   double lo, double hi) {
    all = dir->make<TH1F>((name + "_all").c_str(), "", nbins, lo, hi);
    pass = dir->make<TH1F>((name + "_pass").c_str(), "", nbins, lo, hi);
  }
};

class Phys14Plots : public ModuleBase {
 private:

  double th_pt_acc;
  double th_eta_acc;

  std::string jets_label_;
  TFileDirectory * dir_;

  TH1F *h_gen_h_pt;
  TH1F *h_gen_h_eta;
  TH1F *h_gen_h_phi;
  TH1F *h_gen_h_mass;

  TH1F *h_gen_th_pt;
  TH1F *h_gen_th_eta;
  TH1F *h_gen_th_mode;

  TH1F *h_n_vtx;

  // tau_h reco+decay mode efficiency
  EfficiencyPlot1D th_dm_eff_vs_pt;
  EfficiencyPlot1D th_dm_eff_vs_eta;
  EfficiencyPlot1D th_dm_eff_vs_nvtx;

  EfficiencyPlot1D th0_dm_eff_vs_pt;
  EfficiencyPlot1D th0_dm_eff_vs_eta;
  EfficiencyPlot1D th0_dm_eff_vs_nvtx;

  EfficiencyPlot1D th1_dm_eff_vs_pt;
  EfficiencyPlot1D th1_dm_eff_vs_eta;
  EfficiencyPlot1D th1_dm_eff_vs_nvtx;

  EfficiencyPlot1D th10_dm_eff_vs_pt;
  EfficiencyPlot1D th10_dm_eff_vs_eta;
  EfficiencyPlot1D th10_dm_eff_vs_nvtx;



  TH2F *h_th_mode_table;

  CLASS_MEMBER(Phys14Plots, fwlite::TFileService*, fs)

 public:
  Phys14Plots(std::string const& name);
  virtual ~Phys14Plots();

  virtual int PreAnalysis();
  virtual int Execute(TreeEvent *event);
  virtual int PostAnalysis();
  virtual void PrintInfo();
};

}

#endif