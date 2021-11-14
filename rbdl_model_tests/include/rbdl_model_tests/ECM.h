#include "rbdl_model_tests/RBDLTestPrep.h"
#include "rbdl_model_tests/EigenUtilities.h"
//#include "rbdl_model_tests/Human36Fixture.h"
#include <unordered_map>

//const double TEST_PREC = 1.0e-12;
const double TEST_LAX = 1.0e-7;

struct ECM {
  ECM () {
    ClearLogOutput();
    // clientPtr = RBDLTestPrep::getInstance()->getAMBFClientInstance();
    // clientPtr->connect();


    // baseHandler = clientPtr->getRigidBody(base_name, true);
    // usleep(1000000);

    // //base is rigid body name, not a joint. This is a hacky way to enable ros topics in the 
    // //server side during first execution
    // baseHandler->set_joint_pos(base_name, 0.0f); 

    // tf::Vector3 P_0_w_tf = baseHandler->get_pos();
    // Eigen::Vector3d P_0_w;
    // P_0_w[0]= P_0_w_tf[0];
    // P_0_w[1]= P_0_w_tf[1];
    // P_0_w[2]= P_0_w_tf[2];
    
    // tf::Vector3 R_0_w_tf = baseHandler->get_rpy();

    // Eigen::Matrix3d R_0_w = eigenUtilities.rotation_from_euler<Eigen::Matrix3d>(R_0_w_tf[0], R_0_w_tf[1], R_0_w_tf[2]);

    // T_0_w = eigenUtilities.get_frame<Eigen::Matrix3d, Eigen::Vector3d, Eigen::Matrix4d>(R_0_w, P_0_w);


    rbdlModel = new Model;

    // mass, com - inertia offset, inertia
    baseLink = Body(1., RigidBodyDynamics::Math::Vector3d (-0.0046, 0., 0.0801), 
           RigidBodyDynamics::Math::Vector3d (0., 0., 0.));
    ROOT_baseLinkJoint = Joint(JointTypeFixed);
    ROOT_baseLinkST.E = RigidBodyDynamics::Math::Matrix3dIdentity;
    ROOT_baseLinkST.r = RigidBodyDynamics::Math::Vector3dZero;
    baseLinkId = rbdlModel->AddBody(0, ROOT_baseLinkST, ROOT_baseLinkJoint, baseLink, "baseLink");

    pitchEndLink = Body (2.032, RigidBodyDynamics::Math::Vector3d (0.0513, 0.0048, 0.0008), 
          RigidBodyDynamics::Math::Vector3d (0.0636, 0.0099, 0.0726));
    //baseLink_pitchEndLink = Joint(JointType3DoF);
    // baseLink_pitchEndLinkST.E = 
    // eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(0.0227, 0.0239, 0.9995), 
    //                                         Eigen::Vector3d(0.0229, -0.9995, -0.0227));
    // baseLink_pitchEndLinkST.r = RigidBodyDynamics::Math::Vector3d(0.0001, 0.0, 0.0);
    // pitchEndLinkId = rbdlModel->AddBody(baseLinkId, baseLink_pitchEndLinkST, 
    //                                     baseLink_pitchEndLink, pitchEndLink, "pitchEndLink");    

    yawLink = Body (6.417, RigidBodyDynamics::Math::Vector3d (0.0, -0.0161, 0.1345), 
                  RigidBodyDynamics::Math::Vector3d (0.2978, 0.3125, 0.0449));
    baseLink_yawLinkST.E =
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(-0.0002, -1.0, 0.0), 
                                        Eigen::Vector3d(0.0, 0.0, -1.0));
    baseLink_yawLinkST.r = RigidBodyDynamics::Math::Vector3d(0.0, 0.0, 0.0);
    baseLink_yawLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    yawLinkId = rbdlModel->AddBody(baseLinkId, baseLink_yawLinkST, 
                                      baseLink_yawLinkJoint, yawLink, "yawLink");

    pitchBackLink = Body (0.421, RigidBodyDynamics::Math::Vector3d (-0.0515, -0.1434, -0.009), 
                  RigidBodyDynamics::Math::Vector3d (0.0236, 0.0028, 0.0261));
    yawLink_pitchBackLinkST.E =
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(1.0, 0.0, 0.0), 
                                        Eigen::Vector3d(0.0, 0.0, 1.0));
    yawLink_pitchBackLinkST.r = RigidBodyDynamics::Math::Vector3d(0.0, 0.0098, 0.1624);
    yawLink_pitchBackLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    pitchBackLinkId = rbdlModel->AddBody(yawLinkId, yawLink_pitchBackLinkST, 
                                      yawLink_pitchBackLinkJoint, pitchBackLink, "pitchBackLink");

    pitchBottomLink = Body (0.359, RigidBodyDynamics::Math::Vector3d (0.1491, -0.0182, 0.0), 
              RigidBodyDynamics::Math::Vector3d (0.0007, 0.019, 0.0192));
    pitchBackLink_pitchBottomLinkST.E =
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(0.0, 0.0, 1.0), 
                                        Eigen::Vector3d(0.0, 0.0, 1.0));
    pitchBackLink_pitchBottomLinkST.r = RigidBodyDynamics::Math::Vector3d(-0.1028, -0.2867, 0.0);
    pitchBackLink_pitchBottomLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    pitchBottomLinkId = rbdlModel->AddBody(pitchBackLinkId, pitchBackLink_pitchBottomLinkST, 
                                      pitchBackLink_pitchBottomLinkJoint, pitchBottomLink, 
                                      "pitchBottomLink");

    pitchBottomLink_pitchEndLinkST.E = 
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(0.0, 0.0, 1.0), 
                                            Eigen::Vector3d(0.0, 0.0, 1.0));
    pitchBottomLink_pitchEndLinkST.r = RigidBodyDynamics::Math::Vector3d(0.3401, -0.0001, -0.0005);
    pitchBottomLink_pitchEndLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    pitchEndLinkId = rbdlModel->AddBody(pitchBottomLinkId, pitchBottomLink_pitchEndLinkST, 
                                      pitchBottomLink_pitchEndLinkJoint, pitchEndLink, 
                                      "pitchEndLink");

    mainInsertionLink = Body (0.231, RigidBodyDynamics::Math::Vector3d (-0.059, -0.0165, 0.0008), 
                  RigidBodyDynamics::Math::Vector3d (0.0003, 0.0015, 0.0016));
    pitchEndLink_mainInsertionLinkST.E = 
    // Parent axis, Child axis
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(0.0, 1.0, 0.0), 
                                            Eigen::Vector3d(1.0, 0.0, 0.0));
    // Parent Pivot
    pitchEndLink_mainInsertionLinkST.r = RigidBodyDynamics::Math::Vector3d(0.1031, -0.0961, 0.0001);
    pitchEndLink_mainInsertionLinkJoint = Joint(JointTypePrismatic, Math::Vector3d(1.0, 0.0, 0.0));
    mainInsertionLinkId = rbdlModel->AddBody(pitchEndLinkId, pitchEndLink_mainInsertionLinkST, 
                                      pitchEndLink_mainInsertionLinkJoint, mainInsertionLink, 
                                      "mainInsertionLink");

    toolLink = Body (1.907, RigidBodyDynamics::Math::Vector3d (0., -0.0008, 0.0723), 
                  RigidBodyDynamics::Math::Vector3d (0.0457, 0.0455, 0.0017));
    mainInsertionLink_toolLinkST.E =
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(1.0, 0.0, 0.0), 
                                        Eigen::Vector3d(0.0, 0.0, -1.0));
    mainInsertionLink_toolLinkST.r = RigidBodyDynamics::Math::Vector3d(-0.0108, -0.062, 0.0);
    mainInsertionLink_toolLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    toolLinkId = rbdlModel->AddBody(mainInsertionLinkId, mainInsertionLink_toolLinkST, 
                                      mainInsertionLink_toolLinkJoint, toolLink, "toolLink");

    pitchFrontLink = Body (1.607, RigidBodyDynamics::Math::Vector3d (-0.0365, -0.1526, 0.0), 
              RigidBodyDynamics::Math::Vector3d (0.0983, 0.0175, 0.1099));
    yawLink_pitchFrontLinkST.E = 
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(1.0, 0.0, 0.0), 
                                            Eigen::Vector3d(0.0, 0.0, 1.0));
    yawLink_pitchFrontLinkST.r = RigidBodyDynamics::Math::Vector3d(0.0, 0.0, 0.199);
    yawLink_pitchFrontLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    pitchFrontLinkId = rbdlModel->AddBody(yawLinkId, yawLink_pitchFrontLinkST, 
                                      yawLink_pitchFrontLinkJoint, pitchFrontLink, 
                                      "pitchFrontLink");

    pitchFrontLink_pitchBottomLinkST.E = 
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(0.0, 0.0, 1.0), 
                                            Eigen::Vector3d(0.0, 0.0, 1.0));
    pitchFrontLink_pitchBottomLinkST.r = RigidBodyDynamics::Math::Vector3d(-0.1031, -0.2868, 0.0);
    pitchFrontLink_pitchBottomLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    //pitchBottomLinkId = 
    rbdlModel->AddBody(pitchFrontLinkId, pitchFrontLink_pitchBottomLinkST, 
                                      pitchFrontLink_pitchBottomLinkJoint, pitchBottomLink);//, 
                                      //"pitchBottomLink");

    pitchTopLink = Body (0.439, RigidBodyDynamics::Math::Vector3d (0.1702, -0.0001, 0.0008), 
              RigidBodyDynamics::Math::Vector3d (0.0, 0.0381, 0.0381));
    pitchFrontLink_pitchTopLinkST.E = 
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(0.0, 0.0, 1.0), 
                                            Eigen::Vector3d(0.0, 0.0, 1.0));
    pitchFrontLink_pitchTopLinkST.r = RigidBodyDynamics::Math::Vector3d(-0.1084, -0.3242, 0.0);
    pitchFrontLink_pitchTopLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    pitchTopLinkId = rbdlModel->AddBody(pitchFrontLinkId, pitchFrontLink_pitchTopLinkST, 
                                      pitchFrontLink_pitchTopLinkJoint, pitchTopLink, 
                                      "pitchTopLink");

    pitchTopLink_pitchEndLinkST.E = 
    eigenUtilities.rotationMatrixFromVectors(Eigen::Vector3d(0.0, 0.0, 1.0), 
                                            Eigen::Vector3d(0.0, 0.0, 1.0));
    pitchTopLink_pitchEndLinkST.r = RigidBodyDynamics::Math::Vector3d(0.3404, -0.0002, -0.0006);
    pitchTopLink_pitchEndLinkJoint = Joint(JointTypeRevolute, Math::Vector3d(0.0, 0.0, 1.0));
    //pitchTopLinkId = 
    rbdlModel->AddBody(pitchTopLinkId, pitchTopLink_pitchEndLinkST, 
                                      pitchTopLink_pitchEndLinkJoint, pitchEndLink);//, "pitchEndLink");

    Q = VectorNd::Constant ((size_t) rbdlModel->dof_count, 0.);
    QDot = VectorNd::Constant ((size_t) rbdlModel->dof_count, 0.);
    QDDot = VectorNd::Constant ((size_t) rbdlModel->dof_count, 0.);
    Tau = VectorNd::Constant ((size_t) rbdlModel->dof_count, 0.);

    KUKA_JOINT_LIMITS[ "link1" ] = { -2.094f, 2.094f };
    KUKA_JOINT_LIMITS[ "link2" ] = { -2.094f, 2.094f };
    KUKA_JOINT_LIMITS[ "link3" ] = { -2.094f, 2.094f };
    KUKA_JOINT_LIMITS[ "link4" ] = { -2.094f, 2.094f }; 
    KUKA_JOINT_LIMITS[ "link5" ] = { -2.094f, 2.094f }; 
    KUKA_JOINT_LIMITS[ "link6" ] = { -2.094f, 2.094f }; 
    KUKA_JOINT_LIMITS[ "link7" ] = { -3.054f, 3.054f }; 

    ClearLogOutput();
  }

  ~ECM () {
    delete rbdlModel;
    //clientPtr->cleanUp();
  }

  Model *rbdlModel = nullptr;
  AMBFClientPtr clientPtr = nullptr;
  rigidBodyPtr baseHandler = nullptr;
  std::string base_name = "base";
  Eigen::Matrix4d T_0_w;
  // std::vector<std::vector<float>> KUKA_JOINT_LIMITS;
  std::unordered_map<std::string, std::vector<float>> KUKA_JOINT_LIMITS;
  std::unordered_map<std::string, std::vector<float>>::iterator KUKA_JOINT_LIMITS_itr;

  EigenUtilities eigenUtilities;

  unsigned int baseLinkId, pitchEndLinkId, mainInsertionLinkId, toolLinkId, yawLinkId, 
            pitchBackLinkId, pitchBottomLinkId, pitchFrontLinkId, pitchTopLinkId;

  Body baseLink, pitchEndLink, mainInsertionLink, toolLink, yawLink, 
            pitchBackLink, pitchBottomLink, pitchFrontLink, pitchTopLink;

  Joint ROOT_baseLinkJoint, baseLink_pitchEndLinkJoint, pitchEndLink_mainInsertionLinkJoint, 
        mainInsertionLink_toolLinkJoint, baseLink_yawLinkJoint, yawLink_pitchBackLinkJoint,
        pitchBackLink_pitchBottomLinkJoint, pitchBottomLink_pitchEndLinkJoint,
        yawLink_pitchFrontLinkJoint, pitchFrontLink_pitchBottomLinkJoint, 
        pitchFrontLink_pitchTopLinkJoint, pitchTopLink_pitchEndLinkJoint;

  SpatialTransform ROOT_baseLinkST, baseLink_pitchEndLinkST, pitchEndLink_mainInsertionLinkST, 
        mainInsertionLink_toolLinkST, baseLink_yawLinkST, yawLink_pitchBackLinkST,
        pitchBackLink_pitchBottomLinkST, pitchBottomLink_pitchEndLinkST,yawLink_pitchFrontLinkST, 
        pitchFrontLink_pitchBottomLinkST, pitchFrontLink_pitchTopLinkST, pitchTopLink_pitchEndLinkST;

  VectorNd Q;
  VectorNd QDot;
  VectorNd QDDot;
  VectorNd Tau;
};