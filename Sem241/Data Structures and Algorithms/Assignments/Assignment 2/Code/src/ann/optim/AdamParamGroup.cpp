/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AdamParamGroup.cpp
 * Author: ltsach
 * 
 * Created on October 8, 2024, 1:43 PM
 */

#include "optim/AdamParamGroup.h"

AdamParamGroup::AdamParamGroup(double beta1, double beta2):
    m_beta1(beta1), m_beta2(beta2){
    //Create some maps:
    m_pParams = new xmap<string, xt::xarray<double>*>(&stringHash);
    m_pGrads = new xmap<string, xt::xarray<double>*>(&stringHash);
    m_pFirstMomment = new xmap<string, xt::xarray<double>*>(
            &stringHash,
            0.75,
            0,
            xmap<string, xt::xarray<double>*>::freeValue);
    m_pSecondMomment = new xmap<string, xt::xarray<double>*>(
            &stringHash,
            0.75,
            0,
            xmap<string, xt::xarray<double>*>::freeValue);
    //
    m_step_idx = 1;
    m_beta1_t = m_beta1;
    m_beta2_t = m_beta2;
}

AdamParamGroup::AdamParamGroup(const AdamParamGroup& orig):
    m_beta1(orig.m_beta1), m_beta2(orig.m_beta2){
    m_pParams = new xmap<string, xt::xarray<double>*>(&stringHash);
    m_pGrads = new xmap<string, xt::xarray<double>*>(&stringHash);
    m_pFirstMomment = new xmap<string, xt::xarray<double>*>(
            &stringHash,
            0.75,
            0,
            xmap<string, xt::xarray<double>*>::freeValue);
    m_pSecondMomment = new xmap<string, xt::xarray<double>*>(
            &stringHash,
            0.75,
            0,
            xmap<string, xt::xarray<double>*>::freeValue);
    //copy:
    *m_pParams = *orig.m_pParams;
    *m_pGrads = *orig.m_pGrads;
    *m_pFirstMomment = *orig.m_pFirstMomment;
    *m_pSecondMomment = *orig.m_pSecondMomment;
    //
    m_step_idx = 1;
    m_beta1_t = m_beta1;
    m_beta2_t = m_beta2;
}

AdamParamGroup::~AdamParamGroup() {
    if(m_pFirstMomment != nullptr) delete m_pFirstMomment;
    if(m_pSecondMomment != nullptr) delete m_pSecondMomment;
}

void AdamParamGroup::register_param(string param_name, 
        xt::xarray<double>* ptr_param,
        xt::xarray<double>* ptr_grad){
    //YOUR CODE IS HERE
    m_pParams->put(param_name, ptr_param);
    m_pGrads->put(param_name, ptr_grad);
}
void AdamParamGroup::register_sample_count(unsigned long long* pCounter){
    m_pCounter = pCounter;
}

void AdamParamGroup::zero_grad(){
    //YOUR CODE IS HERE
    DLinkedList<string> keys = m_pGrads->keys();
    for(auto key: keys){
        xt::xarray<double>* pGrad = m_pGrads->get(key);
        xt::xarray<double>* pParam = m_pParams->get(key);
        *pGrad = xt::zeros<double>(pParam->shape());
    }
    //reset sample_counter
    *m_pCounter = 0;
}

void AdamParamGroup::step(double lr) {
    double epsilon = 1e-7; // Small constant to prevent division by zero

    // Get all the parameter names
    DLinkedList<string> keys = m_pGrads->keys();

    // Iterate through each parameter
    for (auto key : keys) {
        // Retrieve the parameter, gradient, first moment, and second moment
        xt::xarray<double>& P = *m_pParams->get(key);
        xt::xarray<double>& grad_P = *m_pGrads->get(key);
        xt::xarray<double>& m_t = *m_pFirstMomment->get(key);
        xt::xarray<double>& v_t = *m_pSecondMomment->get(key);

        m_t = m_beta1 * m_t + (1 - m_beta1) * grad_P;
        v_t = m_beta2 * v_t + (1 - m_beta2) * xt::square(grad_P);
        xt::xarray<double> m_hat = m_t / (1 - m_beta1_t);
        xt::xarray<double> v_hat = v_t / (1 - m_beta2_t);

        P = P - lr * m_hat / (xt::sqrt(v_hat) + epsilon);
    }

    // Step 6: Update step index and exponential decay factors
    m_step_idx += 1;
    m_beta1_t *= m_beta1;
    m_beta2_t *= m_beta2;
}

