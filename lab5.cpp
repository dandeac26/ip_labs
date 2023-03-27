#include "lab5.hh"

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
void utcn::ip::Lab5::runLab() {
  int op;
  do {
    utcn::ip::Lab5::printMenu(LAB_MENU);
    cin >> op;
    switch (op) {
      case 0:
        break;
      case 1:
        Alg1();
        break;
      case 2:
        Alg2();
        break;
      case 3:
        Ex3();
        break;
      case 4:
        Ex4();
        break;
      default:
        cout << "Invalid selection" << std::endl;
    }
  } while (op != 0);
}

#define HEIGHT 500
#define WIDTH 500
void utcn::ip::Lab5::Alg1() {
  cv::Mat src;
  const std::string path_to_src = ASSETS_DIR "Images/letters.bmp";
  src = cv::imread(path_to_src, cv::IMREAD_GRAYSCALE);  // Read the image

  if (!src.data) {
    std::cout << "Could not open or find the image" << std::endl;
    return;
  }

  int height = src.rows;
  int width = src.cols;

  // cv::Mat dst = cv::Mat(height, width, CV_8UC1);
  cv::Mat_<cv::Vec3b> dst(height, width);
  int labels[height][width];
  for (int i = 0; i < height; i++) {  // height -1 maybe
    for (int j = 0; j < width; j++) {
      labels[i][j] = 0;
    }
  }
  int label = 0;
  queue<pair<int, int>> Q;
  pair<int, int> q;
  int di[4] = {-1, 0, 1, 0};
  int dj[4] = {0, -1, 0, 1};
  uchar neighbors[4];

  for (int i = 0; i < height - 1; i++) {  // height -1 maybe
    for (int j = 0; j < width - 1; j++) {
      if (src.at<uchar>(i, j) == 0 && labels[i][j] == 0) {
        label++;
        labels[i][j] = label;
        Q.push({i, j});
        while (!Q.empty()) {
          q = Q.front();
          Q.pop();
          for (int k = 0; k < 4; k++) {
            neighbors[k] = src.at<uchar>(i + di[k], j + dj[k]);
            if (src.at<uchar>(neighbors[k]) == 0 &&
                labels[i + di[k]][j + dj[k]] == 0) {
              labels[i + di[k]][j + dj[k]] = label;
              Q.push({i + di[k], j + dj[k]});
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (labels[i][j] != 0)
        dst(i, j) = cv::Vec3b(255, 0, 255);
      else
        dst(i, j) = cv::Vec3b(255, 255, 255);
    }
  }
  cv::imshow("letters", dst);
  cv::waitKey();
}
int get_min(vector<int> vec) {
  int rez = INT_MAX;
  for (int i = 0; i < vec.size(); i++) {
    rez = min(rez, vec[i]);
  }
  return rez;
}

void utcn::ip::Lab5::Alg2() {
  cv::Mat src;
  const std::string path_to_src = ASSETS_DIR "Images/letters.bmp";
  src = cv::imread(path_to_src, cv::IMREAD_GRAYSCALE);  // Read the image

  if (!src.data) {
    std::cout << "Could not open or find the image" << std::endl;
    return;
  }

  int height = src.rows;
  int width = src.cols;

  // cv::Mat dst = cv::Mat(height, width, CV_8UC1);
  cv::Mat_<cv::Vec3b> dst(height, width);
  int labels[height][width];
  for (int i = 0; i < height; i++) {  // height -1 maybe
    for (int j = 0; j < width; j++) {
      labels[i][j] = 0;
    }
  }

  int label = 0;
  // vector<int> edges[10000];
  vector<vector<int>> edges;

  int di[4] = {0, -1, -1, -1};
  int dj[4] = {-1, -1, 0, 1};
  uchar neighbors[4];
  vector<int> L;
  for (int i = 0; i < height - 1; i++) {  // height -1 maybe
    for (int j = 0; j < width - 1; j++) {
      if (src.at<uchar>(i, j) == 0 && labels[i][j] == 0) {
        for (int k = 0; k < 4; k++) {
          int I = i + di[k];
          int J = j + dj[k];
          // neighbors[k] = src.at<uchar>(i + di[k], j + dj[k]);
          if (labels[I][J] > 0) {
            L.push_back(labels[I][J]);
          }
        }
        if (L.size() == 0) {
          label++;
          labels[i][j] = label;
        } else {
          int x = get_min(L);
          labels[i][j] = x;
          for (int y = 0; y < L.size(); y++) {
            if (L[y] != x) {
              edges[x].push_back(L[y]);
              edges[L[y]].push_back(x);
            }
          }
        }
      }
    }
  }
  int newlabel = 0;
  int newlabels[label + 1];
  for (int i = 0; i < label + 1; i++) {
    newlabels[i] = 0;
  }
  queue<int> Q;
  for (int i = 1; i < label; i++) {
    if (newlabels[i] == 0) {
      newlabel++;
      newlabels[i] = newlabel;
      Q.push(i);

      while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (int y = 0; y < edges[x].size(); y++) {
          if (newlabels[edges[x][y]] == 0) {
            newlabels[edges[x][y]] = newlabel;
            Q.push(edges[x][y]);
          }
        }
      }
    }
  }

  for (int i = 0; i < height - 1; i++) {
    for (int j = 0; j < width - 1; j++) {
      labels[i][j] = newlabels[labels[i][j]];
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // switch(labels[i][j]){
      //   case 0:
      //     dst.at<uchar>(i,j) = 255;
      //     break;
      //   case 1:
      //     dst.at<uchar>(i,j) = 255;
      //     break;

      // }
      if (labels[i][j] != 0)
        dst(i, j) = cv::Vec3b(255, 0, 255);
      else
        dst(i, j) = cv::Vec3b(255, 255, 255);
    }
  }
  cv::imshow("letters", dst);
  cv::waitKey();
}

void utcn::ip::Lab5::Ex3() {
  // IMPLEMENT CODE HERE
}

void utcn::ip::Lab5::Ex4() {
  // IMPLEMENT CODE HERE
}
