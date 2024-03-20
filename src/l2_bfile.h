//
//  l2_bfile.h
//  osc
//
//  Created by Futao Zhang on 31/03/2016.
//  Copyright (c) 2016 Futao Zhang. All rights reserved.
//

#ifndef __osc__l2_bfile__
#define __osc__l2_bfile__

#include "l1_op_geno.h"
#include "l2_efile.h"
using namespace EFILE;
namespace BFILE{

    typedef struct{
        // bim file
        int _autosome_num;
        vector<int> _chr;
        vector<string> _snp_name;
        map<string, int> _snp_name_map;
        vector<double> _genet_dst;
        vector<int> _bp;
        vector<string> _allele1;
        vector<string> _allele2;
        vector<string> _ref_A; // reference allele
        vector<string> _other_A; // the other allele
        uint64_t _snp_num;
        vector<double> _rc_rate;
        vector<int> _include; // initialized in the read_bimfile()
        VectorXf _maf;
        
        // fam file
        vector<string> _fid;
        vector<string> _pid;
        map<string, int> _id_map;
        vector<string> _fa_id;
        vector<string> _mo_id;
        vector<int> _sex;
        vector<double> _pheno;
        uint32_t _pheno_num;
        vector<string> _cov; //cov major, values belong to the same covariate are adjacent
        uint32_t _cov_num;
        vector<double> _qcov;
        uint32_t _qcov_num;
        
        uint64_t _indi_num;
        vector<int> _keep; // initialized in the read_famfile()
        MatrixXd _varcmp_Py; // BLUP solution to the total genetic effects of individuals
        
        // bed file
        vector< vector<bool> > _snp_1;
        vector< vector<bool> > _snp_2;
        
        // imputed data
        bool _dosage_flag;
        vector< vector<float> > _geno_dose;
        vector<double> _impRsq;
        
        // genotypes
        MatrixXd _geno;
        
        vector<double> _mu;
        vector<double> _mr;
        
        MatrixXf _grm_N;
        MatrixXd _grm;
        
        //
        //
        int _reml_mtd;
        int _reml_max_iter;
        int _V_inv_mtd;
        bool _reml_force_inv;
        bool _reml_force_converge;
        bool _reml_no_converge;
        bool _reml_AI_not_invertible;
        MatrixXd _P;
        vector<int> _r_indx;
        vector<int> _r_indx_drop;
        vector<string> _var_name;
        vector<double> _varcmp;
        vector<string> _hsq_name;
        
        bool _within_family;
        vector<int> _fam_brk_pnt;
        vector< SparseMatrix<double> > _Asp;
        vector< SparseMatrix<double> > _Asp_prev;
        double _y_Ssq;
        vector<double> _fixed_rg_val;
        bool _reml_fixed_var;
        VectorXd _b;
        VectorXd _se;
        
        //reserved
        bool _bivar_reml;
        bool _bivar_no_constrain;
        bool _ignore_Ce;
        double _y2_Ssq;
        vector< vector<int> > _bivar_pos;
        vector< vector<int> > _bivar_pos_prev;
        
        double _ncase;
        double _ncase2;
        bool _flag_CC;
        bool _flag_CC2;
        
    } bInfo;
    
    typedef struct{
        char* SNP;
        char* a1;
        char* a2;
        double freq;
        double BETA;
        double SE;
        double T;
        double R2;
        double PVAL;
        double NMISS;
        int BP;
        int CHR;
    } ASSOCRLT;
    
    void keep_indi(bInfo* bdata,string indi_list_file);
    void remove_indi(bInfo* bdata, string indi_list_file);
    void extract_snp(bInfo* bdata, int chr);
    void extract_snp(bInfo* bdata,string snplistfile);
    void exclude_snp(bInfo* bdata,string snplistfile);
    void calcu_mu(bInfo* bdata, bool ssq_flag=false);
    bool make_XMat(bInfo* bdata,vector<uint32_t> &snpids, MatrixXd &X, bool mu=false);
    bool make_XMat(bInfo* bdata, int start, int slide_wind, MatrixXd &X, bool mu=false);
    bool make_XMat_subset(bInfo* bdata, int start, int slide_wind, MatrixXd &X, bool standardise=false);
    bool make_XMat_subset(bInfo* bdata,vector<uint32_t> &snpids, MatrixXd &X, bool standardise=false);
    void read_famfile(bInfo* bdata, string famfile);
    void read_bimfile(bInfo* bdata,string bimfile);
    void read_bedfile(bInfo* bdata, string bedfile);
    void filter_snp_maf(bInfo* bdata,double maf);
    void filter_snp_call(bInfo* bdata,double call);
    void make_grm(bInfo* bdata, int grm_mtd,  bool diag_f3_flag=false);
    void make_grm(bInfo* bdata, MatrixXd &VZ, int grm_mtd,  bool diag_f3_flag=false);
    void read_grm(bInfo* bdata,bool grm_bin_flag, string grm_file, vector<string> &grm_id, bool read_id_only, bool dont_read_N);
    int read_grm_id(bInfo* bdata,string grm_file, vector<string> &grm_id);
    void read_phen(bInfo* bdata, string phen_file, char* mpheno, bool mvFlg);
    void read_cov(bInfo* bdata, string cov_file, bool qcovFlg);
    int construct_X(bInfo* bdata, vector<MatrixXd> &E_float, MatrixXd &qE_float, MatrixXd &_X);
    bool make_Xvec_subset(bInfo* bdata,uint32_t &includeid, VectorXd &vec, bool standardise);
    bool make_Xvec_subset(bInfo* bdata,int &snpid, VectorXd &vec, bool standardise);
    void  testLinear(vector<ASSOCRLT> &assoc_rlts,char* outfileName, bInfo* bdata, MatrixXd &COV_plus);
    void  testLogit(vector<ASSOCRLT> &assoc_rlts,char* outfileName, bInfo* bdata, MatrixXd &COV_plus);
    int comp_assoc(const void *a,const void *b);
    void stepwise_slct(bInfo* bdata,vector<int> &sig, vector<int> &slctid, vector<int> &rmid, vector<ASSOCRLT> &assoc_rlts, double p_cutoff, double fdr_cutoff, bool updatesig, bool swforward,double swrsq);
    void detect_family(bInfo* bdata,  vector<MatrixXd> &_A);
    void init_binfo(bInfo* bdata);
    void free_assoclist(vector<ASSOCRLT> &a);
    void std_XMat_(bInfo* bdata, MatrixXf &X,  VectorXd &sd_SNP, bool miss_with_mu, bool divid_by_std); // for test use
}

#endif /* defined(__osc__l2_bfile__) */
