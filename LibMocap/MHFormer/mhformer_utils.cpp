#include "pch.h"

#include "mhformer_utils.h"

namespace mhf {

#define M_PI 3.14159265359 

	Vector2d GetMockKeypoints() {

		Vector2d keypoints{

			{640.0000f, 360.0000f},
			{605.3012f, 349.5903f},
			{598.3614f, 498.7952f},
			{501.2048f, 526.5542f},
			{674.6988f, 370.4096f},
			{657.3494f, 540.4338f},
			{660.8193f, 696.5783f},
			{662.5542f, 273.2530f},
			{643.4699f, 180.7229f},
			{626.1205f, 155.2771f},
			{623.5180f, 120.5783f},
			{716.3374f, 186.5060f},
			{771.8554f, 252.4337f},
			{709.3976f, 294.0723f},
			{598.3614f, 186.5060f},
			{539.3735f, 231.6144f},
			{598.3614f, 294.0723f}

		};

		return keypoints;

	}

	Vector2d InitVec2d(int Rows, int Cols) {
		Vector2d vec2d(Rows, vector<float>(Cols, 0.0));
		return vec2d;
	}

	Vector3d InitVec3d(int Nt, int Rows, int Cols) {

		Vector3d vec3d;
		for (int i = 0; i < Nt; i++) {
			vec3d.push_back(InitVec2d(Rows, Cols));
		}

		return vec3d;

	}

	Vector4d InitVec4d(int BatchSize, int Nt, int Rows, int Cols) {

		Vector4d vec4d;
		for (int i = 0; i < BatchSize; i++) {
			vec4d.push_back(InitVec3d(Nt, Rows, Cols));
		}

		return vec4d;

	}

	Vector2d AllocatePose2d() {

		const int numJoints = 17;
		const int dims = 2;

		Vector2d pose = InitVec2d(numJoints, dims);

		return pose;

	}


	Vector2d RescaleAndShiftPose2d(Vector2d& Pose2d, int FrameWidth, int FrameHeight) {

		Vector2d pose2d = Pose2d;
		size_t numJoints = pose2d.size();


		// Resale
		float xMin, xMax;
		float yMin, yMax;
		float dx, dy;

		GetPoseMinMax(xMin, xMax, pose2d, 0);
		GetPoseMinMax(yMin, yMax, pose2d, 1);

		dx = xMax - xMin;
		dy = yMax - yMin;

		float ratioTarget = 0.8f;
		float dyTarget = ratioTarget * FrameHeight;
		float ratioY = dyTarget / dy;

		for (int i = 0; i < numJoints; i++) {
			pose2d[i][0] *= ratioY;
			pose2d[i][1] *= ratioY;
		}

		// Shift
		float xCenter = 0.5f * FrameWidth;
		float yCenter = 0.5f * FrameHeight;

		vector<float> center = { xCenter, yCenter };
		vector<float> pelvis = pose2d[0];
		vector<float> shift(2, 0.0);

		shift[0] = center[0] - pelvis[0];
		shift[1] = center[1] - pelvis[1];

		for (int i = 0; i < numJoints; i++) {
			for (int j = 0; j < 2; j++) {
				pose2d[i][j] += shift[j];
			}
		}

		return pose2d;

	}


	Vector2d NormalizeKeypoints2d(Vector2d& Keypoints, int FrameWidth, int FrameHeight) {

		Vector2d keypoints = Keypoints;

		size_t numJoints = Keypoints.size();
		size_t dim2d = Keypoints[0].size();

		for (int i = 0; i < numJoints; i++) {

			keypoints[i][0] = 2.0f * keypoints[i][0] / FrameWidth - 1.0f;
			keypoints[i][1] = 2.0f * keypoints[i][1] / FrameWidth - 1.0f * FrameHeight / FrameWidth;

		}

		return keypoints;

	}

	Vector2d UnnormalizeKeypoints2d(Vector2d& Keypoints, int FrameWidth, int FrameHeight) {

		Vector2d keypoints = Keypoints;

		size_t numJoints = Keypoints.size();
		size_t dim2d = Keypoints[0].size();

		for (int i = 0; i < numJoints; i++) {

			keypoints[i][0] = (keypoints[i][0] + 1.0f) * 0.5f * FrameWidth;
			keypoints[i][1] = (keypoints[i][1] + 1.0f * FrameHeight / FrameWidth) * 0.5f * FrameWidth;

		}

		return keypoints;

	}

	Vector2d NormalizeKeypoints3d(Vector2d& Keypoints, int FrameWidth, int FrameHeight) {

		Vector2d keypoints = Keypoints;

		size_t numJoints = Keypoints.size();
		for (int i = 0; i < numJoints; i++) {

			keypoints[i][0] = 2.0f * keypoints[i][0] / FrameWidth - 1.0f;
			keypoints[i][1] = 2.0f * keypoints[i][1] / FrameWidth - 1.0f * FrameHeight / FrameWidth;
			keypoints[i][2] = 2.0f * keypoints[i][2] / FrameWidth - 1.0f;

		}

		return keypoints;

	}

	Vector2d UnnormalizeKeypoints3d(Vector2d& Keypoints, int FrameWidth, int FrameHeight) {

		Vector2d keypoints = Keypoints;

		size_t numJoints = Keypoints.size();
		for (int i = 0; i < numJoints; i++) {

			keypoints[i][0] = (float)((keypoints[i][0] + 1.0) * 0.5 * FrameWidth);
			keypoints[i][1] = (float)((keypoints[i][1] + 1.0 * FrameHeight / FrameWidth) * 0.5 * FrameWidth);
			keypoints[i][2] = (float)((keypoints[i][2] + 1.0) * 0.5 * FrameWidth);

		}

		return keypoints;

	}

	vector<float> InterpVec1d(vector<float>& InputVec, int OutputSize) {

		int inputSize = (int)InputVec.size();
		std::vector<float> outputVec(OutputSize);

		for (int i = 0; i < OutputSize; ++i) {

			float index = static_cast<float>(i * (inputSize - 1)) / static_cast<float>(OutputSize - 1);
			int index_int = static_cast<int>(index);
			float t = index - index_int;

			outputVec[i] = (1.0f - t) * InputVec[index_int] + t * InputVec[std::min(index_int + 1, inputSize - 1)];
		}

		return outputVec;
	}

	void InterpInputVec(Vector2d& InputVec, int NumFramesOut) {



	}


	Vector4d ConvertKeypointsToInputVec(Vector2d& Keypoints, int BatchSize, int NumFrames) {

		Vector2d keypoints = Keypoints;

		int numJoints = (int)Keypoints.size();
		int dim2d = (int)Keypoints[0].size();

		Vector4d inputVec = InitVec4d(BatchSize, NumFrames, numJoints, dim2d);

		for (int ib = 0; ib < BatchSize; ib++) {
			for (int i = 0; i < NumFrames; i++) {
				for (int j = 0; j < numJoints; j++) {
					for (int k = 0; k < dim2d; k++) {
						inputVec[ib][i][j][k] = Keypoints[j][k];
					}
				}
			}
		}

		return inputVec;

	}

	Vector4d CreateInputVec(Vector3d& TemporalData, int BatchSize, int NumFramesOut) {

		int numFramesIn = (int)TemporalData.size();
		int numJoints = (int)TemporalData[0].size();
		int dim2d = (int)TemporalData[0][0].size();

		Vector4d inputVec = InitVec4d(BatchSize, NumFramesOut, numJoints, dim2d);

		Vector3d data = InitVec3d(numJoints, dim2d, numFramesIn);
		Vector3d dataInterp = InitVec3d(numJoints, dim2d, NumFramesOut);

		// Prepare data for interpolation
		for (int i = 0; i < numFramesIn; i++) {
			for (int j = 0; j < numJoints; j++) {
				for (int k = 0; k < dim2d; k++) {
					data[j][k][i] = TemporalData[i][j][k];
				}
			}
		}

		for (int j = 0; j < numJoints; j++) {
			for (int k = 0; k < dim2d; k++) {
				dataInterp[j][k] = InterpVec1d(data[j][k], NumFramesOut);
			}
		}

		// Input vector
		for (int ib = 0; ib < BatchSize; ib++) {
			for (int i = 0; i < NumFramesOut; i++) {
				for (int j = 0; j < numJoints; j++) {
					for (int k = 0; k < dim2d; k++) {
						inputVec[ib][i][j][k] = dataInterp[j][k][i];
					}
				}
			}
		}

		return inputVec;

	}

	Ort::Value CreateTensor(Vector4d& Vec, vector<float>& Buffer, Ort::MemoryInfo& Info) {

		int64_t batchSize = Vec.size();
		int64_t numFrames = Vec[0].size();
		int64_t numJoints = Vec[0][0].size();
		int64_t dims = Vec[0][0][0].size();

		int index = 0;
		for (int ib = 0; ib < batchSize; ib++) {
			for (int i = 0; i < numFrames; i++) {
				for (int j = 0; j < numJoints; j++) {
					for (int k = 0; k < dims; k++) {
						Buffer[index] = Vec[ib][i][j][k];
						index++;
					}
				}
			}
		}

		const std::array<int64_t, 4> Shape = { 1, numFrames, numJoints, dims };

		Ort::Value Tensor = Ort::Value::CreateTensor<float>(Info, Buffer.data(),
			Buffer.size(), Shape.data(), Shape.size());

		return Tensor;

	}

	Vector2d ConvertOutputTensorToPose3d(Ort::Value& Outputs) {

		int numJoints = 17;
		int dims = 3;

		Vector2d pose = InitVec2d(numJoints, dims);
		for (int i = 0; i < numJoints; i++) {
			for (int j = 0; j < dims; j++) {
				pose[i][j] = Outputs.At<float>({ 0, 0, i, j });
			}
		}

		return pose;

	}

	void GetPoseMinMax(float& Min, float& Max, Vector2d& PoseIn, int Direct) {

		size_t numJoints = PoseIn.size();

		vector<float> data;
		for (int i = 0; i < numJoints; i++) {
			data.push_back(PoseIn[i][Direct]);
		}

		auto it = std::minmax_element(data.begin(), data.end());
		Min = *it.first;
		Max = *it.second;

	}

	Vector2d RescaleAndShiftPose3d(Vector2d& Pose3d, Vector2d& Pose2d) {

		Vector2d pose3d = Pose3d;

		size_t numJoints = pose3d.size();
		int dims = 3;

		float yMinP2d, yMaxP2d;
		float yMinP3d, yMaxP3d;

		GetPoseMinMax(yMinP2d, yMaxP2d, Pose2d, 1);
		GetPoseMinMax(yMinP3d, yMaxP3d, Pose3d, 1);

		float dyP2d, dyP3d;
		dyP2d = yMaxP2d - yMinP2d;
		dyP3d = yMaxP3d - yMinP3d;

		float ratioY;
		ratioY = dyP2d / dyP3d;

		for (int i = 0; i < numJoints; i++) {
			pose3d[i][0] *= ratioY;
			pose3d[i][1] *= ratioY;
			pose3d[i][2] *= ratioY;
		}

		// Shift pose
		float targetPelvisX = Pose2d[0][0];
		float targetPelvisY = Pose2d[0][1];
		float targetPelvisZ = targetPelvisX;

		float shiftX = targetPelvisX - pose3d[0][0];
		float shiftY = targetPelvisY - pose3d[0][1];
		float shiftZ = targetPelvisZ - pose3d[0][2];
		for (int i = 0; i < numJoints; i++) {

			pose3d[i][0] += shiftX;
			pose3d[i][1] += shiftY;
			pose3d[i][2] += shiftZ;

		}

		return pose3d;

	}

	Vector2d RotatePose3dAroundX(Vector2d& Pose3d, float AngleDeg) {

		Vector2d pose3d = Pose3d;
		size_t numJoints = pose3d.size();

		for (int i = 0; i < numJoints; i++) {
			pose3d[i] = RotateAroundX(pose3d[i], AngleDeg);
		}

		return pose3d;

	}

	vector<float> RotateAroundX(vector<float>& Vec, float AngleDeg) {

		std::vector<float> result(3);
		float rad = (float)(AngleDeg * M_PI / 180);  // 將角度轉換為弧度

		result[0] = Vec[0];  // x 座標不變
		result[1] = Vec[1] * std::cos(rad) - Vec[2] * std::sin(rad);  // y' = y*cos(θ) - z*sin(θ)
		result[2] = Vec[1] * std::sin(rad) + Vec[2] * std::cos(rad);  // z' = y*sin(θ) + z*cos(θ)

		return result;

	}
	Vector2d ToPixelSpace(Vector2d& PoseIn, int Width, int Height) {

		Vector2d pose = PoseIn;

		size_t numJoints = pose.size();
		int dims = 3;

		for (int i = 0; i < numJoints; i++) {
			pose[i][0] *= Width;
			pose[i][1] *= Height;
			pose[i][2] *= Width;
		}

		return pose;

	}

	void PrintPoint(string Msg, vector<float>& Point, int Dims) {

		string outMsg = "";
		outMsg += Msg;
		outMsg += ": ";
		for (int i = 0; i < Dims; i++) {
			outMsg += "[" + std::to_string(Point[i]) + "]";
		}

		cout << outMsg << endl;

	}

} // Namespace