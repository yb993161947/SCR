#include "ImageRectify.h"
#include <Eigen/StdVector>
#include <QtMath>
#include <opencv2/legacy/compat.hpp>

EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(Vector2d);

using namespace cv;
DxImageRectify::DxImageRectify(void)
{
    m_vtAdjustPt.clear();
    m_vtXPotPt.clear();
    m_dAdjustPointDis = 0.0;
}


DxImageRectify::~DxImageRectify(void)
{
}

bool DxImageRectify::FindIdealPts(const int nWidth, const int nHeight, MatrixXd& imgpts, MatrixXd& out_boardpts, MatrixXd& idealpts)
{
    MatrixXd BoardPts(48, 2);
    BoardPts << 1, 3, 1, 4, 1, 5, 1, 6, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 3, 1, 3, 2, 3, 3, 3, 4, 3,
        5, 3, 6, 3, 7, 3, 8, 4, 1, 4, 2, 4, 3, 4, 6, 4, 7, 4, 8, 5, 1, 5, 2, 5, 3, 5, 6, 5, 7, 5, 8, 6, 1,
        6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7, 6, 8, 7, 2, 7, 3, 7, 4, 7, 5, 7, 6, 7, 7, 8, 3, 8, 4, 8, 5, 8, 6;

    Vector2d center(nWidth / 2, nHeight / 2);
    vector<Vector2d> imgpts_center;
    imgpts_center.clear();

    for (int i = 0; i < imgpts.rows(); i++)
    {
        Vector2d imgptstranspose = imgpts.row(i).transpose();

        if ((imgptstranspose - center).norm() < nImgCenterToAdPtDis &&
            CheckIfAdjustPoint(imgptstranspose[0], imgptstranspose[1], nWidth / 2, nHeight / 2))
        {
            imgpts_center.push_back(imgpts.row(i).transpose());
        }
    }
    vector<Vector2d> vtidealpts;
    vector<Vector2d> vtAdjustPt;
    vector<int> vtErrorPairCenter;
    vtErrorPairCenter.clear();

    MatrixXd CurrentBoardPts;
    while (1)
    {
        CurrentBoardPts = BoardPts;
        vtidealpts.clear();
        vtAdjustPt.clear();
        double mindist = nWidth;
        int mindistpt1, mindistpt2;
        mindistpt1 = mindistpt2 = -1;

        for (int i = 0; i < imgpts_center.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {

                bool bErrorPairCenter = false;
                for (int k = 0; k < vtErrorPairCenter.size() / 2; k++)
                {
                    if (i == vtErrorPairCenter[2 * k] && j == vtErrorPairCenter[2 * k + 1])
                    {
                        bErrorPairCenter = true;
                        break;
                    }
                }
                if (bErrorPairCenter)
                {
                    continue;
                }
                double a = (imgpts_center[i] - imgpts_center[j]).norm();
                if (a < mindist && (a > nMinAdjustPtDis && a < nMaxAdjustPtDis))
                {
                    mindist = a;
                    mindistpt1 = i;
                    mindistpt2 = j;
                }
            }
        }

        vtErrorPairCenter.push_back(mindistpt1);
        vtErrorPairCenter.push_back(mindistpt2);

        m_dAdjustPointDis = mindist;
        if (mindistpt1 == -1)
        {
            return false;
        }

        CurrentBoardPts = CurrentBoardPts * mindist;

        Vector2d t_vec = imgpts_center[mindistpt2] - imgpts_center[mindistpt1];
        double theta = atan2(t_vec(1), t_vec(0));
        Matrix2d rot;
        rot << cos(theta), -sin(theta), sin(theta), cos(theta);
        Matrix2d m;
        m << t_vec, center - imgpts_center[mindistpt1];
        if (m.determinant() < 0)
        {
            rot.col(1) *= -1;
        }
        for (int i = 0; i < CurrentBoardPts.rows(); i++)
        {
            CurrentBoardPts.row(i) = (rot * CurrentBoardPts.row(i).transpose()).transpose();
        }
        Vector2d trans_vec = imgpts_center[mindistpt1] - CurrentBoardPts.row(20).transpose();
        for (int i = 0; i < CurrentBoardPts.rows(); i++)
        {
            CurrentBoardPts.row(i) += trans_vec.transpose();
        }

        for (int i = 0; i < imgpts.rows(); i++)
        {
            for (int j = 0; j < CurrentBoardPts.rows(); j++)
            {
                if ((imgpts.row(i) - CurrentBoardPts.row(j)).norm() < fMinDisOfTwoCircle)
                {

                    Vector2d idealpt = CurrentBoardPts.row(j).transpose();
                    vtidealpts.push_back(idealpt);

                    Vector2d adjustpt = imgpts.row(i).transpose();
                    vtAdjustPt.push_back(adjustpt);

                    break;
                }
            }
        }
        if (vtidealpts.size() < nMinAdjustPtNum)
        {
            continue;
        }
        else
        {
            break;
        }
        int nErrorPairCenterNum = vtErrorPairCenter.size() / 2;
        int nAllPairCenterNum = (imgpts_center.size() * (imgpts_center.size() - 1)) / 2;
        if (nErrorPairCenterNum >= nAllPairCenterNum)
        {
            return false;
        }
    }


    idealpts.resize(vtidealpts.size(), 2);
    imgpts.resize(vtAdjustPt.size(), 2);

    for (unsigned i = 0; i < vtidealpts.size(); i++)
    {
        idealpts.row(i) = vtidealpts[i];
    }

    for (unsigned i = 0; i < vtAdjustPt.size(); i++)
    {
        imgpts.row(i) = vtAdjustPt[i];
    }
    out_boardpts = CurrentBoardPts;
    return true;
}

Mat DxImageRectify::Refine(const Mat& input, const MatrixXd& imgpts, const MatrixXd& idealpts)
{
    assert(imgpts.rows() == idealpts.rows());
    assert(imgpts.cols() == idealpts.cols() && idealpts.cols() == 2);
    Mat refinedImage(input.rows, input.cols, CV_8U);
    int rows = imgpts.rows();
    MatrixXd X = MatrixXd(rows, 10);
    VectorXd wx = VectorXd(10);
    VectorXd wy = VectorXd(10);
    VectorXd idealx = idealpts.col(0);
    ArrayXXd idealxa = idealx.array();
    VectorXd idealy = idealpts.col(1);
    ArrayXXd idealya = idealy.array();


    VectorXd imgx = imgpts.col(0);
    VectorXd imgy = imgpts.col(1);
    X << MatrixXd::Constant(rows, 1, 1), idealx, idealy, (idealxa * idealxa).matrix(),
        (idealxa * idealya).matrix(), (idealya * idealya).matrix(),
        (idealxa * idealxa * idealxa).matrix(), (idealxa * idealxa * idealya).matrix(),
        (idealxa * idealya * idealya).matrix(), (idealya * idealya * idealya).matrix();

    wx = X.colPivHouseholderQr().solve(imgx);
    wy = X.colPivHouseholderQr().solve(imgy);

    uint8_t* data = (uint8_t*) refinedImage.data;
    uint8_t* input_p = (uint8_t*) input.data;
    double dWx[10], dWy[10];

    for (int i = 0; i < 10; i++)
    {
        dWx[i] = wx[i];
        dWy[i] = wy[i];
    }

    for (int i = 0; i < input.rows; i++)
    {
        for (int j = 0; j < input.cols; j++)
        {
            double x = j;
            double y = i;
            double xx = dWx[0] + dWx[1] * x + dWx[2] * y + dWx[3] * x * x + dWx[4] * x * y +
                dWx[5] * y * y + dWx[6] * x * x * x + dWx[7] * x * x * y +
                dWx[8] * x * y * y + dWx[9] * y * y * y;
            double yy = dWy[0] + dWy[1] * x + dWy[2] * y + dWy[3] * x * x + dWy[4] * x * y +
                dWy[5] * y * y + dWy[6] * x * x * x + dWy[7] * x * x * y +
                dWy[8] * x * y * y + dWy[9] * y * y * y;

            int xxi = int(xx + 0.5);
            int yyi = int(yy + 0.5);
            if (xxi < 0 || xxi >= input.cols || yyi < 0 || yyi >= input.rows)
                data[input.cols * i + j] = 0;
            else
                data[input.cols * i + j] = input_p[input.cols * yyi + xxi];
        }
    }

    return refinedImage;
}

DxImageRectify::Result DxImageRectify::AdjustImage(const cv::Mat& src_image, cv::Mat& refined_image, cv::Mat& refined_circle_removed_image)
{
    if (src_image.type() != CV_8UC1)
    {
        return InputImageIllegal;
    }
    vector<Vec3f> vtCirclept;
    vtCirclept.clear();
    FindCirclePt(src_image, nAdjustCircleRadius, nMinAdjustHoghtParam, vtCirclept);
    m_vtAdjustPt = vtCirclept;

    unsigned nCircleNum = m_vtAdjustPt.size();
    if (nCircleNum < nMinAdjustPtNum)
    {
        return NotEnoughAjustPoints;
    }

    MatrixXd idealpts, imgpts, allboardpts;
    int nImgpts_count = 0;
    imgpts.resize(m_vtAdjustPt.size(), 2);
    for (size_t i = 0; i < m_vtAdjustPt.size(); i++)
    {
        imgpts.row(nImgpts_count) << m_vtAdjustPt[i][0], m_vtAdjustPt[i][1];
        nImgpts_count++;
    }

    imgpts.conservativeResize(nImgpts_count, 2);
    bool bFind = FindIdealPts(src_image.cols, src_image.rows, imgpts, allboardpts, idealpts);
    if (!bFind)
    {
        return CannotFindCenterPoints;
    }

    Mat refined = Refine(src_image, imgpts, idealpts);

    vtCirclept.clear();
    FindCirclePt(refined, nAdjustCircleRadius, nMinAdjustHoghtParam, vtCirclept);
    m_vtAdjustPt = vtCirclept;

    vtCirclept.clear();
    FindCirclePt(refined, nXpotCircleRadius, nMinXpotHoghtParam, vtCirclept);
    m_vtXPotPt = vtCirclept;

    MatrixXd matXPotPt;
    matXPotPt.resize(m_vtXPotPt.size(), 2);
    for (size_t i = 0; i < m_vtXPotPt.size(); i++)
    {
        matXPotPt.row(i) << m_vtXPotPt[i][0], m_vtXPotPt[i][1];
    }

    refined.copyTo(refined_image);

    cv::Mat mask = cv::Mat::zeros(refined.rows, refined.cols, CV_8UC1);
    for (int i = 0; i < m_vtAdjustPt.size(); i++)
    {
        cv::circle(mask, cv::Point(m_vtAdjustPt[i][0], m_vtAdjustPt[i][1]),
            nRemoveAdCircleRadius, cv::Scalar(1), CV_FILLED);
    }
    for (int i = 0; i < m_vtXPotPt.size(); i++)
    {
        cv::circle(mask, cv::Point(m_vtXPotPt[i][0], m_vtXPotPt[i][1]),
                nRemoveXpCircleRadius,cv::Scalar(1), CV_FILLED);
    }
    cv::inpaint(refined, mask, refined_circle_removed_image, 2, INPAINT_TELEA);

    return Success;
}

void DxImageRectify::GetAdjustPt(vector<Vec3f>& vtAdjustPt)
{
    vtAdjustPt.clear();
    vtAdjustPt = m_vtAdjustPt;
}

void DxImageRectify::GetxSPotPt(vector<Vec3f>& vtXPotPt)
{
    vtXPotPt.clear();
    vtXPotPt = m_vtXPotPt;
}

void DxImageRectify::FindCirclePt(const cv::Mat& src_image_8bit, int nRadius, int nMinAdjustCenternum, vector<Vec3f>& vtCirclept)
{
    Mat resultImg;
    Mat src_image_blur_8bit;
    medianBlur(src_image_8bit, src_image_blur_8bit, 3);

    Canny(src_image_blur_8bit, resultImg, nMinCannyParam, nMaxCannyParam, 3);

    uint8_t* inputImageData = (uint8_t*) src_image_blur_8bit.data;
    uint8_t* resultImageData = (uint8_t*) resultImg.data;

    vector<CircleInfo> vecCircleInfo, vecaccCenterSeedPoint;

    int nMinRadius = 0;
    int nMaxRadius = 0;
    if (nRadius == nAdjustCircleRadius)
    {
        nMinRadius = nMinAdjustCircleRadius;
        nMaxRadius = nMaxAdjustCircleRadius;
    }
    else if (nRadius == nXpotCircleRadius)
    {
        nMinRadius = nMinXpotCircleRadius;
        nMaxRadius = nMaxXpotCircleRadius;
    }
    for (int nR = nMinRadius; nR <= nMaxRadius; nR++)
    {
        ProbabilityHoughTransform(resultImageData, inputImageData, resultImg.rows, resultImg.cols,
            nR, nMinAdjustCenternum, false, 2, vecCircleInfo);
    }
    FindSameCenter(vecCircleInfo, vecaccCenterSeedPoint);

    for (int i = 0; i < vecaccCenterSeedPoint.size(); i++)
    {
        float fCenterX = 0.0f;
        float fCenterY = 0.0f;
        float fRadius = 0.0f;

        vector<Vec2d> vecCirlceEdgePt;
        vecCirlceEdgePt.clear();

        GetCirlceEdgePt(inputImageData, resultImageData, resultImg.rows, resultImg.cols, 2, false,
            vecaccCenterSeedPoint[i].nCenterX, vecaccCenterSeedPoint[i].nCenterY,
            vecaccCenterSeedPoint[i].nRadius, vecCirlceEdgePt);

        int nCount = vecCirlceEdgePt.size();
        if (nCount < 6)
        {
            continue;
        }
        CvPoint2D32f* PointArray2D32f = (CvPoint2D32f*) malloc(nCount * sizeof(CvPoint2D32f));
        ;
        for (int j = 0; j < nCount; j++)
        {
            PointArray2D32f[j].x = (float) vecCirlceEdgePt[j][0];
            PointArray2D32f[j].y = (float) vecCirlceEdgePt[j][1];
        }
        CvBox2D* box = (CvBox2D32f*) malloc(sizeof(CvBox2D32f));
        ;
        cvFitEllipse(PointArray2D32f, nCount, box);

        fCenterX = box->center.x;
        fCenterY = box->center.y;
        fRadius = (box->size.width * 0.5 + box->size.height * 0.5) / 2;

        if (cvRound(fRadius) > nMaxRadius || cvRound(fRadius) < nMinRadius ||
            fabs(box->size.width - box->size.height) > 5 ||
            !CheckSeedPointIsAccCenter(fCenterX, fCenterY, vecCirlceEdgePt) ||
            !CheckIfCirleByColor(inputImageData, resultImg.rows, resultImg.cols, fCenterX, fCenterY, fRadius))
        {
            continue;
        }

        vtCirclept.push_back(Vec3f(fCenterX, fCenterY, fRadius));
    }
}

bool DxImageRectify::FitCircle3Points(float fX[], float fY[], float& fCenterX, float& fCenterY, float& fRadius)
{
    float sr1, sr2, sr3; // square of radius
    float Y12, Y13, X12, X13;

    // solve equations
    Y12 = fY[0] - fY[1];
    Y13 = fY[0] - fY[2];
    X12 = fX[0] - fX[1];
    X13 = fX[0] - fX[2];

    float fCenterXScale = X12 * Y13 - X13 * Y12;
    if (fabs(fCenterXScale) < eps)
        return false;

    sr1 = fX[0] * fX[0] + fY[0] * fY[0];
    sr2 = fX[1] * fX[1] + fY[1] * fY[1];
    sr3 = fX[2] * fX[2] + fY[2] * fY[2];

    fCenterX = (sr1 - sr2) * Y13 - (sr1 - sr3) * Y12;
    fCenterX = fCenterX / fCenterXScale * 0.5f;

    if (fabs(Y12) >= eps)
        fCenterY = (float) ((sr1 - sr2 - 2.0f * X12 * fCenterX) / (2.0f * Y12));
    else if (fabs(Y13) >= eps)
        fCenterY = (float) ((sr1 - sr3 - 2.0f * X13 * fCenterX) / (2.0f * Y13));
    else
        return false;

    fRadius = 0;
    for (int i = 0; i < 3; i++)
    {
        fRadius +=
            sqrtf((float) ((fX[i] - fCenterX) * (fX[i] - fCenterX) + (fY[i] - fCenterY) * (fY[i] - fCenterY)));
    }
    fRadius /= 3;

    return true;
}

bool DxImageRectify::CheckSeedPointIsAccCenter(uint8_t* inPixels,
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
    float& fRadius)
{

    if (x1 < nMaxRadius || x1 > nWidth - nMaxRadius || y1 < nMaxRadius ||
        y1 > nHeight - nMaxRadius || inPixels == NULL || cannyPixel == NULL)
    {
        return false;
    }

    int x0 = (x1 < 2) ? 0 : x1 - 2;
    int x2 = (x1 >= nWidth - 2) ? (nWidth - 2) : x1 + 2;
    int y0 = (y1 < 2) ? y1 : y1 - 2;
    int y2 = (y1 >= nHeight - 2) ? (nHeight - 2) : y1 + 2;

    if (bBlackCircle)
    {
        for (int x = x0; x < x2; x++)
        {
            for (int y = y0; y < y2; y++)
            {
                if (inPixels[x + y * nWidth] > nMaxFeaturePixel || inPixels[x + y * nWidth] < nMinFeaturePixel)
                {
                    return false;
                }
            }
        }
    }

    vector<int> vtEdgePtx;
    vtEdgePtx.clear();
    vector<int> vtEdgePty;
    vtEdgePty.clear();

    for (int x = x1 + 1; x <= x1 + nMaxRadius; x++)
    {
        if (cannyPixel[x + y1 * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x);
            vtEdgePty.push_back(y1);
            break;
        }
    }

    for (int x = x1 - 1; x >= x1 - nMaxRadius; x--)
    {
        if (cannyPixel[x + y1 * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x);
            vtEdgePty.push_back(y1);
            break;
        }
    }

    for (int y = y1 - 1; y >= y1 - nMaxRadius; y--)
    {
        if (cannyPixel[x1 + y * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x1);
            vtEdgePty.push_back(y);
            break;
        }
    }

    for (int y = y1 + 1; y <= y1 + nMaxRadius; y++)
    {
        if (cannyPixel[x1 + y * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x1);
            vtEdgePty.push_back(y);
            break;
        }
    }

    int nMaxR = int(float(nMaxRadius / sqrt(2)) + 0.5f);
    int nMinR = int(float(nMinRadius / sqrt(2)) - 0.5f);
    for (int x = x1 - 1, y = y1 - 1; x >= x1 - nMaxR && y >= y1 - nMaxR; x--, y--)
    {
        if (cannyPixel[x + y * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x);
            vtEdgePty.push_back(y);
            break;
        }
    }

    for (int x = x1 + 1, y = y1 - 1; x <= x1 + nMaxR && y >= y1 - nMaxR; x++, y--)
    {
        if (cannyPixel[x + y * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x);
            vtEdgePty.push_back(y);
            break;
        }
    }

    for (int x = x1 - 1, y = y1 + 1; x >= x1 - nMaxR && y <= y1 + nMaxR; x--, y++)
    {
        if (cannyPixel[x + y * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x);
            vtEdgePty.push_back(y);
            break;
        }
    }

    for (int x = x1 + 1, y = y1 + 1; x <= x1 + nMaxR && y <= y1 + nMaxR; x++, y++)
    {
        if (cannyPixel[x + y * nWidth] == nWhiteColor)
        {
            vtEdgePtx.push_back(x);
            vtEdgePty.push_back(y);
            break;
        }
    }

    if (vtEdgePtx.size() >= 5)
    {
        float nSumfCenterX = 0.0f;
        float nSumfCenterY = 0.0f;
        float nSumRadius = 0.0f;
        int nCircle = 0;

        for (unsigned i = 0; i < vtEdgePtx.size() - 2; i++)
        {
            float fX[3] = { float(vtEdgePtx[i]), float(vtEdgePtx[i + 1]), float(vtEdgePtx[i + 2]) };
            float fY[3] = { float(vtEdgePty[i]), float(vtEdgePty[i + 1]), float(vtEdgePty[i + 2]) };
            if (FitCircle3Points(fX, fY, fCenterX, fCenterY, fRadius))
            {
                nCircle++;
                nSumfCenterX += fCenterX;
                nSumfCenterY += fCenterY;
                nSumRadius += fRadius;
            }
        }

        for (unsigned i = 0; i < vtEdgePtx.size() - 2; i++)
        {

            for (unsigned j = i + 1; j < vtEdgePtx.size() - 1; j++)
            {
                for (unsigned k = j + 1; k < vtEdgePtx.size(); k++)
                {
                    float fX[3] = { float(vtEdgePtx[i]), float(vtEdgePtx[j]), float(vtEdgePtx[k]) };
                    float fY[3] = { float(vtEdgePty[i]), float(vtEdgePty[j]), float(vtEdgePty[k]) };

                    if (FitCircle3Points(fX, fY, fCenterX, fCenterY, fRadius))
                    {
                        if (cvRound(fRadius) > nMaxRadius || cvRound(fRadius) < nMinRadius)
                        {
                            continue;
                        }

                        nCircle++;
                        nSumfCenterX += fCenterX;
                        nSumfCenterY += fCenterY;
                        nSumRadius += fRadius;
                    }
                }
            }
        }
        fCenterX = nSumfCenterX / nCircle;
        fCenterY = nSumfCenterY / nCircle;
        fRadius = nSumRadius / nCircle;

        if (cvRound(fRadius) > nMaxRadius || cvRound(fRadius) < nMinRadius)
        {
            return false;
        }

        int nCount = 0;
        for (unsigned i = 0; i < vtEdgePtx.size(); i++)
        {
            int x = vtEdgePtx[i];
            int y = vtEdgePty[i];

            float fNorGx = 0.0f;
            float fNorGy = 0.0f;
            float fGradient = 0.0f;
            GetPixelGradient(inPixels, nWidth, nHeight, x, y, bBlackCircle, fNorGx, fNorGy, fGradient);

            float fvecx = vtEdgePtx[i] - fCenterX;
            float fvecy = vtEdgePty[i] - fCenterY;
            float fNorvecx = fvecx / (sqrt(fvecx * fvecx + fvecy * fvecy));
            float fNorvecy = fvecy / (sqrt(fvecx * fvecx + fvecy * fvecy));

            float fAngle = acos(fNorGx * fNorvecx + fNorGy * fNorvecy) * fAngleOfHalfCircle / M_PI;
            if (fAngle > fAngleOfGradientAndCirlce)
            {
                nCount++;
            }
        }
        if (nCount > 1 || (vtEdgePtx.size() == 5 && nCount != 0))
        {
            return false;
        }

        return true;
    }

    return false;
}

void DxImageRectify::FindSameCenter(vector<CircleInfo>& vecCirCleInfo, vector<CircleInfo>& vecaccCenterSeedPoint)
{
    vector<bool> vtFlag(vecCirCleInfo.size(), false);
    vecaccCenterSeedPoint.clear();

    for (int i = 0; i < vecCirCleInfo.size(); i++)
    {
        if (vtFlag[i] == false)
        {
            CircleInfo stCI = vecCirCleInfo[i];
            vtFlag[i] = true;
            for (int j = i + 1; j < vecCirCleInfo.size(); j++)
            {
                double fdisx = vecCirCleInfo[j].nCenterX - vecCirCleInfo[i].nCenterX;
                double fdisy = vecCirCleInfo[j].nCenterY - vecCirCleInfo[i].nCenterY;
                if (sqrt(fdisx * fdisx + fdisy * fdisy) < fMinDisOfTwoCircle)
                {
                    vtFlag[j] = true;
                    if (stCI.nCount < vecCirCleInfo[j].nCount)
                    {
                        stCI = vecCirCleInfo[j];
                    }
                }
            }
            vecaccCenterSeedPoint.push_back(stCI);
        }
    }
}

void DxImageRectify::GetPixelGradient(uint8_t* uimageData,
    int width,
    int height,
    int x,
    int y,
    bool bBlackToWhite,
    float& fNorGx,
    float& fNorGy,
    float& fGradient)
{

    uint8_t bPixel[9];
    memset(bPixel, 0, sizeof(uint8_t) * 9);

    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            if (x + i > width - 1 || x + i < 0 || (y + j) > height - 1 || (y + j) < 0)
            {
                continue;
            }
            bPixel[i + 1 + (j + 1) * 3] = uimageData[(x + i) + (y + j) * width];
        }
    }

    // Sobel
    float fGx = float((-1.0f) * bPixel[0] + bPixel[2] + (-2.0f) * bPixel[3] + 2.0f * bPixel[5] +
        (-1.0f) * bPixel[6] + bPixel[8]);
    float fGy = float((-1.0f) * bPixel[0] + (-2.0f) * bPixel[1] + (-1.0f) * bPixel[2] + bPixel[6] +
        2.0f * bPixel[7] + bPixel[8]);

    fNorGx = fGx / (sqrt(fGx * fGx + fGy * fGy));
    fNorGy = fGy / (sqrt(fGx * fGx + fGy * fGy));
    if (!bBlackToWhite)
    {
        fNorGx = -fNorGx;
        fNorGy = -fNorGy;
    }
    fGradient = sqrt(fGx * fGx + fGy * fGy);
}

int DxImageRectify::ProbabilityHoughTransform(uint8_t* pSoberPixel,
    uint8_t* uimageData,
    int nWidth,
    int nHeight,
    int nRadius,
    int nMinAdjustCenternum,
    bool bBlackToWhite,
    int nCountSize,
    vector<CircleInfo>& vecaccCenterSeedPoint)
{
    int* nAcc = new int[nWidth * nHeight];
    memset(nAcc, 0, sizeof(int) * nWidth * nHeight);

    int x0, y0;
    double t;

    for (int x = 0; x < nWidth; x++)
    {
        for (int y = 0; y < nHeight; y++)
        {
            if (pSoberPixel[x + y * nWidth] == nWhiteColor)
            {
                float fNorGx, fNorGy, fGradient;
                fNorGx = fNorGy = fGradient = 0.0f;
                GetPixelGradient(uimageData, nWidth, nHeight, x, y, bBlackToWhite, fNorGx, fNorGy, fGradient);

                x0 = x + fNorGx * nRadius;
                y0 = y + fNorGy * nRadius;

                for (int i = max(0, x0 - nCountSize); i <= min(x0 + nCountSize, nWidth - 1); i++)
                {
                    for (int j = max(0, y0 - nCountSize); j <= min(y0 + nCountSize, nHeight - 1); j++)
                    {
                        if (i == x0 && j == y0)
                        {
                            nAcc[i + j * nWidth] += 2;
                        }
                        else
                        {
                            nAcc[i + j * nWidth] += 1;
                        }
                    }
                }
            }
        }
    }

    bool** bFlag = new bool*[nWidth];
    for (int i = 0; i < nWidth; i++)
    {
        bFlag[i] = new bool[nHeight];
        memset(bFlag[i], false, sizeof(bool) * nHeight);
    }

    bool bAeraMax = true;
    for (int x = 0; x < nWidth; x++)
    {
        for (int y = 0; y < nHeight; y++)
        {
            if (nAcc[x + y * nWidth] > nMinAdjustCenternum)
            {
                bAeraMax = true;
                for (int i = max(0, x - nRadius / 2); i <= min(x + nRadius / 2, nWidth - 1); i++)
                {
                    for (int j = max(0, y - nRadius / 2); j <= min(y + nRadius / 2, nHeight - 1); j++)
                    {
                        if (nAcc[x + y * nWidth] < nAcc[i + j * nWidth])
                        {
                            bAeraMax = false;
                            break;
                        }
                    }
                    if (!bAeraMax)
                    {
                        break;
                    }
                }
                if (bAeraMax)
                {
                    CircleInfo stCI;
                    stCI.nCenterX = x;
                    stCI.nCenterY = y;
                    stCI.nRadius = nRadius;
                    stCI.nCount = nAcc[x + y * nWidth];
                    vecaccCenterSeedPoint.push_back(stCI);
                }
            }
        }
    }

    delete[] nAcc;

    for (int i = 0; i < nWidth; i++)
    {
        delete[] bFlag[i];
    }
    delete[] bFlag;
    return 0;
}

void DxImageRectify::GetCirlceEdgePt(uint8_t* uimageData,
    uint8_t* cannyPixels,
    int nWidth,
    int nHeight,
    int nCountSize,
    bool bBlackToWhite,
    int nCenterX,
    int nCenterY,
    int nRadius,
    vector<Vec2d>& vecCirlceEdgePt)
{
    for (int x = min(nCenterX - nRadius - 5, 0); x < max(nCenterX + nRadius + 5, nWidth); x++)
    {
        for (int y = min(nCenterY - nRadius - 5, 0); y < max(nCenterY + nRadius + 5, nHeight); y++)
        {
            if (cannyPixels[x + y * nWidth] == nWhiteColor)
            {
                float fNorGx, fNorGy, fGradient;
                fNorGx = fNorGy = fGradient = 0.0f;
                GetPixelGradient(uimageData, nWidth, nHeight, x, y, bBlackToWhite, fNorGx, fNorGy, fGradient);

                int x0 = x + fNorGx * nRadius;
                int y0 = y + fNorGy * nRadius;

                for (int i = max(0, x0 - nCountSize); i <= min(x0 + nCountSize, nWidth - 1); i++)
                {
                    for (int j = max(0, y0 - nCountSize); j <= min(y0 + nCountSize, nHeight - 1); j++)
                    {
                        if (i == nCenterX && j == nCenterY)
                        {
                            vecCirlceEdgePt.push_back(Vec2d(x, y));
                        }
                    }
                }
            }
        }
    }
}

double DxImageRectify::GetDistanceofAdjustPt()
{
    return 28.0 / m_dAdjustPointDis;
}

bool DxImageRectify::CheckSeedPointIsAccCenter(float fCenterX, float fCenterY, vector<Vec2d>& vecCirlceEdgePt)
{
    vector<int> vect;
    vect.clear();
    for (int i = 0; i < vecCirlceEdgePt.size(); i++)
    {
        float fX = vecCirlceEdgePt[i][0] - fCenterX;
        float fY = vecCirlceEdgePt[i][1] - fCenterY;

        float fRadian = atan2(fY, fX);

        int nPos = int(fRadian * 12.0f / M_PI);
        nPos = fRadian > 0 ? nPos + 1 : nPos - 1;

        bool bHas = false;
        for (int j = 0; j < vect.size(); j++)
        {
            if (vect[j] == nPos)
            {
                bHas = true;
                break;
            }
        }
        if (!bHas)
        {
            vect.push_back(nPos);
        }
    }

    if (vect.size() >= 12)
    {
        return true;
    }

    return false;
}

bool DxImageRectify::CheckIfAdjustPoint(float x, float y, float fImageCenterX, float fImageCenterY, bool bNearPt /*= false*/)
{
    int nMinDisPtIndex = 0;
    vector<int> vtErrorPt;
    vector<int> vtCorrectPt;
    CheckNearPtNumOfAdjustPoint(x, y, vtErrorPt, vtCorrectPt);

    float fCenterDis =
        sqrt((x - fImageCenterX) * (x - fImageCenterX) + (y - fImageCenterY) * (y - fImageCenterY));
    if ((vtErrorPt.size() >= vtCorrectPt.size() && vtCorrectPt.size() < 2) || fCenterDis < nMaxAdjustPtDis)
    {
        return false;
    }

    if (vtCorrectPt.size() >= 2)
    {
        for (int i = 0; i < vtCorrectPt.size() - 1; i++)
        {
            for (int j = i + 1; j < vtCorrectPt.size(); j++)
            {
                float fDotMultip =
                    ((m_vtAdjustPt[vtCorrectPt[i]][0] - x) * (m_vtAdjustPt[vtCorrectPt[j]][0] - x) +
                    (m_vtAdjustPt[vtCorrectPt[i]][1] - y) * (m_vtAdjustPt[vtCorrectPt[j]][1] - y)) /
                        (sqrt((m_vtAdjustPt[vtCorrectPt[i]][0] - x) * (m_vtAdjustPt[vtCorrectPt[i]][0] - x) +
                    (m_vtAdjustPt[vtCorrectPt[i]][1] - y) * (m_vtAdjustPt[vtCorrectPt[i]][1] - y)) *
                            sqrt((m_vtAdjustPt[vtCorrectPt[j]][0] - x) * (m_vtAdjustPt[vtCorrectPt[j]][0] - x) +
                            (m_vtAdjustPt[vtCorrectPt[j]][1] - y) * (m_vtAdjustPt[vtCorrectPt[j]][1] - y)));
                if ((acos(fDotMultip) * 180 / M_PI > 85 && acos(fDotMultip) * 180 / M_PI < 95) ||
                    acos(fDotMultip) * 180 / M_PI < 5 || acos(fDotMultip) * 180 / M_PI > 175)
                {
                    return true;
                }
            }
        }
        return false;
    }

    if (!bNearPt)
    {
        for (int i = 0; i < vtErrorPt.size(); i++)
        {
            float dis = sqrt((x - m_vtAdjustPt[vtErrorPt[i]][0]) * (x - m_vtAdjustPt[vtErrorPt[i]][0]) +
                (y - m_vtAdjustPt[vtErrorPt[i]][1]) * (y - m_vtAdjustPt[vtErrorPt[i]][1]));
            if (dis > nMinAdjustPtDis)
            {
                continue;
            }

            bool bNearCorrect =
                CheckIfAdjustPoint(m_vtAdjustPt[vtErrorPt[i]][0], m_vtAdjustPt[vtErrorPt[i]][0],
                    fImageCenterX, fImageCenterY, true);
            if (bNearCorrect)
            {
                return false;
            }

            int nIndex = 0;
            vector<int> vtNearErrorPt;
            vector<int> vtNearCorrectPt;
            CheckNearPtNumOfAdjustPoint(m_vtAdjustPt[vtErrorPt[i]][0], m_vtAdjustPt[vtErrorPt[i]][0],
                vtNearErrorPt, vtNearCorrectPt);
            float fNearVariance =
                CalPtDisVariance(m_vtAdjustPt[vtErrorPt[i]][0], m_vtAdjustPt[vtErrorPt[i]][0],
                    vtNearErrorPt, vtNearCorrectPt);
            float fVariance = CalPtDisVariance(x, y, vtErrorPt, vtCorrectPt);
            if (fVariance > fNearVariance)
            {
                return false;
            }
        }
    }

    return true;
}

void DxImageRectify::CheckNearPtNumOfAdjustPoint(float x, float y, vector<int>& vtErrorPt, vector<int>& vtCorrectPt)
{
    float fMinDis = 10000;
    vtErrorPt.clear();
    vtCorrectPt.clear();

    for (int i = 0; i < m_vtAdjustPt.size(); i++)
    {
        float dis = sqrt((x - m_vtAdjustPt[i][0]) * (x - m_vtAdjustPt[i][0]) +
            (y - m_vtAdjustPt[i][1]) * (y - m_vtAdjustPt[i][1]));
        if (dis < 5)
        {
            continue;
        }

        if (dis < nMinAdjustPtDis || (dis > nMaxAdjustPtDis && dis < 150.0f))
        {
            vtErrorPt.push_back(i);
        }
        else if (dis > nMinAdjustPtDis && dis < nMaxAdjustPtDis)
        {
            vtCorrectPt.push_back(i);
        }
    }
}

float DxImageRectify::CalPtDisVariance(float x, float y, vector<int>& vtErrorPt, vector<int>& vtCorrectPt)
{
    float fSumDis = 0;


    int nNearPtSize = vtCorrectPt.size() + vtErrorPt.size();
    for (int i = 0; i < vtCorrectPt.size(); i++)
    {
        fSumDis += sqrt((x - m_vtAdjustPt[vtCorrectPt[i]][0]) * (x - m_vtAdjustPt[vtCorrectPt[i]][0]) +
            (y - m_vtAdjustPt[vtCorrectPt[i]][1]) * (y - m_vtAdjustPt[vtCorrectPt[i]][1]));
    }

    for (int i = 0; i < vtErrorPt.size(); i++)
    {
        fSumDis += sqrt((x - m_vtAdjustPt[vtErrorPt[i]][0]) * (x - m_vtAdjustPt[vtErrorPt[i]][0]) +
            (y - m_vtAdjustPt[vtErrorPt[i]][1]) * (y - m_vtAdjustPt[vtErrorPt[i]][1]));
    }

    float fAverageDis = fSumDis / nNearPtSize;

    float fVariance = 0;
    for (int i = 0; i < vtCorrectPt.size(); i++)
    {
        float fDis = sqrt((x - m_vtAdjustPt[vtCorrectPt[i]][0]) * (x - m_vtAdjustPt[vtCorrectPt[i]][0]) +
            (y - m_vtAdjustPt[vtCorrectPt[i]][1]) * (y - m_vtAdjustPt[vtCorrectPt[i]][1]));

        fVariance += (fDis - fAverageDis) * (fDis - fAverageDis);
    }

    for (int i = 0; i < vtErrorPt.size(); i++)
    {
        float fDis = sqrt((x - m_vtAdjustPt[vtErrorPt[i]][0]) * (x - m_vtAdjustPt[vtErrorPt[i]][0]) +
            (y - m_vtAdjustPt[vtErrorPt[i]][1]) * (y - m_vtAdjustPt[vtErrorPt[i]][1]));

        fVariance += (fDis - fAverageDis) * (fDis - fAverageDis);
    }

    return fVariance;
}

bool DxImageRectify::CheckIfCirleByColor(uint8_t* uimageData, int nWidth, int nHeight, float fCenterX, float fCenterY, float fRadius)
{
    return true;
    int nCenterX = cvRound(fCenterX);
    int nCenterY = cvRound(fCenterY);
    int nOuterSquareLen = cvRound(sqrt(fRadius * fRadius * 2)) + 2;
    int nInnerSquareLen = cvRound(fRadius / sqrt(2)) - 1;

    int nInnerSumColor = 0;
    int nOuterSumColor = 0;
    int nInnerSumSize = 0;
    int nOuterSumSize = 0;

    for (int x = max(0, nCenterX - nOuterSquareLen); x < min(nWidth - 1, nCenterX + nOuterSquareLen); x++)
    {
        for (int y = max(0, nCenterY - nOuterSquareLen); y < min(nWidth - 1, nCenterY + nOuterSquareLen); y++)
        {
            if (uimageData[x + y * nWidth] < 5)
            {
                continue;
            }
            if (abs(x - nCenterX) <= nInnerSquareLen && abs(y - nCenterY) <= nInnerSquareLen)
            {
                nInnerSumColor += uimageData[x + y * nWidth];
                nInnerSumSize++;
            }
            else
            {
                nOuterSumColor += uimageData[x + y * nWidth];
                nOuterSumSize++;
            }
        }
    }

    float fInnerAverageColor = float(nInnerSumColor) / float(nInnerSumSize);
    float fOuterAverageColor = float(nOuterSumColor) / float(nOuterSumSize);

    if (fOuterAverageColor > fInnerAverageColor)
    {
        return true;
    }

    return false;
}
