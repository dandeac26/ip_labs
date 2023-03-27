#ifndef LAB5_HH
#define LAB5_HH

#include "lab.hh"

namespace utcn::ip {
class Lab5 : public Lab {
  static inline std::map<int, std::string> LAB_MENU = {
      {1, "alg1\n"},
      {2, "Alg2\n"},
      {3, "Display the center of mass of the selected object"},
      {4, "Ex4\n"},
  };

  static void Alg1();
  static void Alg2();
  static void Ex3();
  static void Ex4();
  static void Ex5();

 public:
  void runLab() override;
};
}  // namespace utcn::ip

#endif  // LAB5_HH
