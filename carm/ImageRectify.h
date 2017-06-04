#ifndef DxImageRectify_H
#define DxImageRectify_H
#pragma once
#include "stdint.h"
#include <Eigen/Eigen>
#include <Eigen/LU>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;

const int nAdjustCircleRadius = 7;
const int nXpotCircleRadius = 11;
const int nMinAdjustPtDis = 110;
const int nMaxAdjustPtDis = 130;
const int nImgCenterToAdPtDis = 250;
const int nMinAdjustHoghtParam = 40;
const int nMinXpotHoghtParam = 50;
const int nMinBoneBoltHoghtParam = 50;

const int nMinAdjustCircleRadius = 5;
const int nMaxAdjustCircleRadius = 9;
const int nMinXpotCircleRadius = 10;
const int nMaxXpotCircleRadius = 17;
const int nMinBoneBoltCircleRadius = 16;
const int nMaxBoneBoltCircleRadius = 40;

const int nRemoveAdCircleRadius = 12;
const int nRemoveXpCircleRadius = 18;

const int nMinAdjustPtNum = 20;
const float fMinDisOfTwoCircle = 10.0f;

const float fAngleOfCircle = 360.0f;
const float fAngleOfHalfCircle = 180.0f;
const float fAngleOfGradientAndCirlce = 45.0f;

const int nBlackColor = 0;
const int nWhiteColor = 255;
const int nColorSize = 256;

const int nMinCannyParam = 20;
const int nMaxCannyParam = 50;

const int nMinBoltCannyParam = 40;
const int nMaxBoltCannyParam = 80;

const float eps = 0.0001f;

const int SUCCESS_ADJUST_POINT = 0;
const int ERROR_ADJUST_POINT_IS_TOO_LACK = -1;
const int ERROR_FIND_CENTER_POINT = -2;
const int ERROR_INPUT_IMAGE_IS_NOT_LEGAL = -3;

typedef struct ImageInfo_t
{
    uint16_t* ImgPixel;
    int nWidth;
    int nHeight;
    double dScale;

    ImageInfo_t()
    {
        ImgPixel = NULL;
        nWidth = 0;
        nHeight = 0;
        dScale = 1.0f;
    }

    ImageInfo_t(const ImageInfo_t& image)
    {
        ImgPixel = image.ImgPixel;
        nWidth = image.nWidth;
        nHeight = image.nHeight;
        dScale = image.dScale;
    }
    ImageInfo_t& operator=(const ImageInfo_t& image)
    {
        ImgPixel = image.ImgPixel;
        nWidth = image.nWidth;
        nHeight = image.nHeight;
        dScale = image.dScale;
        return *this;
    }

} ImageInfo;

typedef struct CircleInfo_t
{
    int nCenterX;
    int nCenterY;
    int nRadius;
    int nCount;
} CircleInfo;
class DxImageRectify
{
public:
    DxImageRectify(void);
    ~DxImageRectify(void);

    enum Result
    {
        Success = 0,
        NotEnoughAjustPoints,
        CannotFindCenterPoints,
        InputImageIllegal,
    };
    Result AdjustImage(const cv::Mat& inputImg, cv::Mat& refined_image, cv::Mat& refined_circle_removed_image);

    void GetAdjustPt(vector<cv::Vec3f>& vtAdjustPt);
    void GetxSPotPt(vector<cv::Vec3f>& vtXPotPt);

    double GetDistanceofAdjustPt();

private:
    cv::Mat Refine(const cv::Mat& input, const MatrixXd& imgpts, const MatrixXd& idealpts);
    bool FindIdealPts(const int nWidth, const int nHeight, MatrixXd& imgpts, MatrixXd& out_boardpts, MatrixXd& idealpts);
    void FindCirclePt(const cv::Mat& src_image_8bit, int nRadius, int nMinAdjustCenternum, vector<cv::Vec3f>& vtCirclept);

    bool CheckSeedPointIsAccCenter(uint8_t* inPixels,
                                   uint8_t* cannyPixel,
                                   int nWidth,
                                   int nHeight,
                                   int x1,
                                   int y1,
                                   int nMinRadius,
                                   int nMaxRadius,
                                   int nMinFeaturePixel,
                                   int nMaxFeaturePixel,
                                   bool bBlackCircle,
                                   float& fCenterX,
                                   float& fCenterY,
                                   float& fRadius);

    bool FitCircle3Points(float fX[], float fY[], float& fCenterX, float& fCenterY, float& fRadius);

    void FindSameCenter(vector<CircleInfo>& vecCirCleInfo, vector<CircleInfo>& vecaccCenterSeedPoint);

    void GetPixelGradient(uint8_t* uimageData,
                          int width,
                          int height,
                          int x,
                          int y,
                          bool bBlackToWhite,
                          float& fNorGx,
                          float& fNorGy,
                          float& fGradient);

    int ProbabilityHoughTransform(uint8_t* pSoberPixel,
                                  uint8_t* uimageData,
                                  int nWidth,
                                  int nHeight,
                                  int nRadius,
                                  int nMinAdjustCenternum,
                                  bool bBlackToWhite,
                                  int nCountSize,
                                  vector<CircleInfo>& vecaccCenterSeedPoint);

    void GetCirlceEdgePt(uint8_t* uimageData,
                         uint8_t* cannyPixels,
                         int nWidth,
                         int nHeight,
                         int nCountSize,
                         bool bBlackToWhite,
                         int nCenterX,
                         int nCenterY,
                         int nRadius,
                         vector<cv::Vec2d>& vecCirlceEdgePt);

    bool CheckSeedPointIsAccCenter(float fCenterX, float fCenterY, vector<cv::Vec2d>& vecCirlceEdgePt);

    void CheckNearPtNumOfAdjustPoint(float x, float y, vector<int>& vtErrorPt, vector<int>& vtCorrectPt);
    bool CheckIfAdjustPoint(float x, float y, float fImageCenterX, float fImageCenterY, bool bNearPt = false);
    float CalPtDisVariance(float x, float y, vector<int>& vtErrorPt, vector<int>& vtCorrectPt);

    bool CheckIfCirleByColor(uint8_t* uimageData, int nWidth, int nHeight, float fCenterX, float fCenterY, float fRadius);

    vector<cv::Vec3f> m_vtAdjustPt;
    vector<cv::Vec3f> m_vtXPotPt;
    double m_dAdjustPointDis;
};
#endif
