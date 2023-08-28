#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <iostream>
#include "Eigen/Dense"


namespace kf {

using namespace std;
using namespace Eigen;

using Eigen::MatrixXd;
using Eigen::VectorXd;


class KalmanFilter {
public:

    KalmanFilter() {

	}

    ~KalmanFilter() {

	}

    void Init(MatrixXd& Fin, MatrixXd& Hin, MatrixXd& Rin, MatrixXd& Qin, int dim) {
	    /*
	    Initializes Kalman filter
	    @param x_in Initial state
	    @param P_in Initial state covariance
	    @param Fin Transition matrix
	    @param Hin Measurement matrix
	    @param Rin Measurement covariance matrix
	    @param Qin Process covariance matrix
	    */

	    mF = Fin;
        mH = Hin;
        mR = Rin;
        mQ = Qin;
        mDims = dim;

	    mFlagDisappear = true;
	    mZeroCount = 0;

    }

    void Preprocess(Eigen::VectorXd& z, Eigen::VectorXd& x, Eigen::MatrixXd& P) {

        if (z(0) != 0 && mFlagDisappear == true) {

            mFlagDisappear = false;
            x(0) = z(0);
            x(1) *= 0.1;
            P = 0 * MatrixXd::Identity(mDims, mDims);
        }

        if (x(0) != 0 && z(0) == 0) {

            z(0) = x(0);
            mZeroCount = mZeroCount + 1;

        } else {

            mZeroCount = 0;

        }

        if (mZeroCount >= 5) {

            mZeroCount = 0;
            mFlagDisappear = true;
            x = VectorXd::Zero(mDims);
            P = 0 * MatrixXd::Identity(mDims, mDims);

        }

    }

    void Postprocess(Eigen::VectorXd& x, VectorXd& output) {

        if (abs(x(1)) > 10) {
            output(0) = 0;
        } else {
            output(0) = (x(0));
        }

        if (x(0) < 0) {
            output(0) = 0;
        }
    }

    void Predict(VectorXd& x, MatrixXd& P) {
        /*
        Prediction Predicts the state and the state covariance
        using the process model
        @param delta_T Time between k and k+1 in s
        */

        //Use the state using the state transition matrix
        x = mF * x;//+mG * mU;
        //Update the covariance matrix using the process noise and state transition matrix
        MatrixXd Ft = mF.transpose();
        P = mF * P * Ft + mQ;

    }


    void Update(const VectorXd& z, VectorXd& x, MatrixXd& P) {
        /*
        Updates the state by using standard Kalman Filter equations
        @param z The measurement at k+1
        */

        // init H AND R
        MatrixXd Ht = mH.transpose();
        MatrixXd PHt = P * Ht;

        MatrixXd Test(int(1), int(1));
        Test(0) = z(0);
        VectorXd y = Test - mH * x;
        MatrixXd S = mH * PHt + mR;
        MatrixXd K = PHt * S.inverse();

        //Update State
        x = x + (K * y);

        mStateX = x;

        //Update covariance matrix
        long x_size = x.size();
        MatrixXd I = MatrixXd::Identity(x_size, x_size);
        P = (I - K * mH) * P;

    }

    VectorXd GetStateX() {
		return mStateX;
	}

private:

    VectorXd mStateX = VectorXd::Zero(2);

	// state transition matrix
	Eigen::MatrixXd mF;
	// process covariance matrix
	Eigen::MatrixXd mQ;
	// measurement matrix
	Eigen::MatrixXd mH;
	// measurement covariance matrix
	Eigen::MatrixXd mR;

	int mDims;

	Eigen::VectorXd mG;
	Eigen::VectorXd mU;

	bool mFlagDisappear;
	int mZeroCount;

};


}

#endif // KALMAN_FILTER_H