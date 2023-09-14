#pragma once

#include "KalmanFilter.hpp"

using namespace Eigen;

namespace zen_math {

	class Kalman1d {

	public:

		Kalman1d() {
		}

		~Kalman1d() {
		}

		void Init(VectorXd StateX, float dt, float Pvar, float Qvar, float Rvar) {

			mStateX = StateX;

			// State transition
			mF(0, 0) = 1.0;
			mF(0, 1) = dt;
			mF(1, 0) = 0.0;
			mF(1, 1) = 1.0;

			// Observe
			mH(0, 0) = 1.0;
			mH(0, 1) = 0.0;

			mP(0, 0) = Pvar;
			mP(0, 1) = 0.0;
			mP(1, 0) = 0.0;
			mP(1, 1) = Pvar;

			mQ(0, 0) = Qvar;
			mQ(0, 1) = 0.0;
			mQ(1, 0) = 0.0;
			mQ(1, 1) = Qvar;

			mR(0, 0) = Rvar;

			mKalman.Init(mF, mH, mR, mQ, 2);
		}
		void Update(VectorXd z) {

			//mKalman.Preprocess(z, mStateX, mP);
			mKalman.Predict(mStateX, mP);
			mKalman.Update(z, mStateX, mP);

		}

		float GetPosition() {
			return mKalman.GetStateX()(0);
		}

		float GetVelocity() {
			return mKalman.GetStateX()(1);
		}

	private:

		const int mDims = 2;

		KalmanFilter mKalman;

		VectorXd mStateX = VectorXd::Zero(mDims);
		MatrixXd mF = MatrixXd::Zero(mDims, mDims);
		MatrixXd mH = MatrixXd::Zero(1, mDims);
		MatrixXd mP = MatrixXd::Zero(mDims, mDims);
		MatrixXd mQ = MatrixXd::Zero(mDims, mDims);
		MatrixXd mR = MatrixXd::Zero(1, 1);
	};

}
