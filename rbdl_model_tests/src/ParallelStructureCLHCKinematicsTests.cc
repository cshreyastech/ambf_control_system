#include "rbdl_model_tests/ParallelStructureCL.h"

TEST_CASE_METHOD(ParallelStructure,
                 __FILE__"_TestInverseKinematicSimple", "") {
  std::vector<unsigned int> body_ids;
  std::vector<RigidBodyDynamics::Math::Vector3d> body_points;
  std::vector<RigidBodyDynamics::Math::Vector3d> target_pos;

  Q[0] = 0.0;
  Q[1] = 0.1;
  Q[2] = 0.1;

  VectorNd Qres = VectorNd::Zero ((size_t) rbdlPSModel->dof_count);

  unsigned int body_id = l4Id;
  RigidBodyDynamics::Math::Vector3d body_point = RigidBodyDynamics::Math::Vector3d (1., 0., 0.);
  RigidBodyDynamics::Math::Vector3d target (1.3, 0., 0.);

  body_ids.push_back (l4Id);
  body_points.push_back (body_point);
  target_pos.push_back (target);

  ClearLogOutput();
  bool res = InverseKinematics (*rbdlPSModel, Q, body_ids, body_points, target_pos,
                                Qres);
  //	cout << LogOutput.str() << endl;
  CHECK (true == res);

  UpdateKinematicsCustom (*rbdlPSModel, &Qres, NULL, NULL);

  RigidBodyDynamics::Math::Vector3d effector;
  effector = CalcBodyToBaseCoordinates(*rbdlPSModel, Qres, body_id, body_point, false);

  CHECK_THAT (target, AllCloseVector(effector, TEST_PREC, TEST_PREC));
}

/*
TEST_CASE_METHOD(ParallelStructure, __FILE__"_TestPSNeutralPosition", "") 
{

  // isConstrainedSystemFullyActuated
  // InverseDynamicsConstraints
  // InverseDynamicsConstraintsRelaxed
    //Test to see if this model is compatiable with the exact IDC operator
  bool isCompatible = isConstrainedSystemFullyActuated(
                        *rbdlPSModel, Q,QDot,cs);
  CHECK(!isCompatible);

  Q[3] = M_PI_4;

  // ForwardDynamics(*rbdlPSModel, Q, QDot, Tau, QDDot);
  // std::vector<std::string> joints = baseHandler->get_joint_names();
  // std::vector<std::string> baseChildren = baseHandler->get_children_names();

  // CHECK (baseChildren.size() == Q.size());

  // for(int i = 0; i < 20; i++)
  // {
  //   for(std::string joint : joints)
  //   {
  //     baseHandler->set_joint_pos<std::string>(joint, 0.0f);
  //   }

  //   usleep(250000);
  // }

  // Q.setZero();

  // for(std::string body : baseChildren)
  // {
  //   unsigned int rbdlBodyId = rbdlPSModel->GetBodyId(body.c_str());

  //   // AMBF body does not exist in RBDL model
  //   if(rbdlBodyId != std::numeric_limits<unsigned int>::max())
  //   // if(rbdlBodyId < rbdlPSModel->mBodies.size())
  //   {
  //     std::cout << "Executing Test case for body: "<< body << ", " << rbdlBodyId << std::endl;

  //     rigidBodyPtr rigidBodyHandler = clientPtr->getRigidBody(body, true);
      
  //     // n - respective body frame
  //     const tf::Quaternion quat_n_w_tf = rigidBodyHandler->get_rot();
  //     const tf::Vector3 P_n_w_tf = rigidBodyHandler->get_pos();

  //     RigidBodyDynamics::Math::Quaternion quat_n_w_ambf;
  //     quat_n_w_ambf(0) = quat_n_w_tf[0];
  //     quat_n_w_ambf(1) = quat_n_w_tf[1];
  //     quat_n_w_ambf(2) = quat_n_w_tf[2];
  //     quat_n_w_ambf(3) = quat_n_w_tf[3];

  //     const RigidBodyDynamics::Math::Matrix3d R_n_w_ambf = quat_n_w_ambf.toMatrix();

  //     RigidBodyDynamics::Math::Vector3d P_n_w_ambf;
  //     P_n_w_ambf.setZero();
      
  //     P_n_w_ambf(0) = P_n_w_tf[0];
  //     P_n_w_ambf(1) = P_n_w_tf[1];
  //     P_n_w_ambf(2) = P_n_w_tf[2];

  //     const RigidBodyDynamics::Math::Matrix3d R_n_w_rbdl =
  //                                       CalcBodyWorldOrientation(*rbdlPSModel, Q, rbdlBodyId, true);
  //     const RigidBodyDynamics::Math::Vector3d P_n_0_rbdl = 
  //                                       CalcBodyToBaseCoordinates(*rbdlPSModel, Q, rbdlBodyId, 
  //                                           RigidBodyDynamics::Math::Vector3d(0., 0., 0.), true);

  //     const RigidBodyDynamics::Math::Vector3d P_n_w_rbdl = T_0_w.block<3, 3>(0, 0) * P_n_0_rbdl;

  //     CHECK_THAT(R_n_w_ambf, AllCloseMatrix(R_n_w_rbdl, TEST_PREC, TEST_PREC));
  //     CHECK_THAT(P_n_w_ambf, AllCloseMatrix(P_n_w_rbdl, TEST_PREC, TEST_PREC));
    // }
  // }
}


TEST_CASE_METHOD(ParallelStructure, __FILE__"_TestPSPIbyFourPosition", "") 
{
  bool isCompatible = isConstrainedSystemFullyActuated(
                        *rbdlPSModel, Q,QDot,cs);
  CHECK(isCompatible);

  //mBody in RBDL has AMBF Joints
  std::map<std::string, unsigned int > mBodyNameMap = rbdlPSModel->mBodyNameMap;
  std::map<std::string, unsigned int>::iterator mBodyNameMapItr;
  for(mBodyNameMapItr = mBodyNameMap.begin(); mBodyNameMapItr != mBodyNameMap.end(); mBodyNameMapItr++)
  {
    std::string bodyName = mBodyNameMapItr->first;
    unsigned int bodyId = mBodyNameMapItr->second;
    std::string parentName = rbdlPSModel->GetBodyName(rbdlPSModel->GetParentBodyId(bodyId));
    std::cout << parentName << ", " << bodyName << ", " << bodyId << std::endl;
    
  }

  ForwardDynamics(*rbdlPSModel, Q, QDot, Tau, QDDot);
  std::vector<std::string> joints = baseHandler->get_joint_names();
  std::vector<std::string> baseChildren = baseHandler->get_children_names();

  CHECK (baseChildren.size() == Q.size());

  std::string activation_joint_name = "l2-l3";
  Q.setZero();

  std::unordered_map<std::string, float> q_desired;
  std::unordered_map<std::string, float>::iterator q_desiredItr;

  q_desired[activation_joint_name] = M_PI_4;

  int activation_joint_id = baseHandler->get_joint_idx_from_name(activation_joint_name.c_str());
  std::cout << "activation_joint_id: " << activation_joint_id << std::endl;

  if(baseHandler->is_joint_idx_valid(activation_joint_id))
  {
    for(int i = 0; i < 20; i++)
    {
      baseHandler->set_joint_pos<std::string>(activation_joint_name, q_desired[activation_joint_name]);
      usleep(250000);

      for(int i = 0; i < joints.size(); i++)
      {
        std::string joint = joints.at(i);
        std::string body = baseChildren.at(i);

        unsigned int rbdlBodyId = rbdlPSModel->GetBodyId(joint.c_str());
        float joint_angle = baseHandler->get_joint_pos<std::string>(joint);

        q_desired[body] = joint_angle;
      }
    }

    for(q_desiredItr = q_desired.begin(); q_desiredItr!=q_desired.end(); ++q_desiredItr)
    {
      std::string body = q_desiredItr->first;
      float joint_angle = q_desiredItr->second;

      unsigned int rbdlBodyId = rbdlPSModel->GetBodyId(body.c_str());
      if(rbdlBodyId != std::numeric_limits<unsigned int>::max() && rbdlBodyId < rbdlPSModel->mBodies.size())
      {
        rbdlBodyId--;
        Q[rbdlBodyId] = joint_angle;
      }
    }

    for(std::string body : baseChildren)
    {
      unsigned int rbdlBodyId = rbdlPSModel->GetBodyId(body.c_str());

      // AMBF body does not exist in RBDL model
      if(rbdlBodyId != std::numeric_limits<unsigned int>::max())
      // if(rbdlBodyId < rbdlPSModel->mBodies.size())
      {
        std::cout << "Executing Test case for body: "<< body << ", " << rbdlBodyId << std::endl;

        rigidBodyPtr rigidBodyHandler = clientPtr->getRigidBody(body, true);
        
        // n - respective body frame
        const tf::Quaternion quat_n_w_tf = rigidBodyHandler->get_rot();
        const tf::Vector3 P_n_w_tf = rigidBodyHandler->get_pos();

        RigidBodyDynamics::Math::Quaternion quat_n_w_ambf;
        quat_n_w_ambf(0) = quat_n_w_tf[0];
        quat_n_w_ambf(1) = quat_n_w_tf[1];
        quat_n_w_ambf(2) = quat_n_w_tf[2];
        quat_n_w_ambf(3) = quat_n_w_tf[3];

        const RigidBodyDynamics::Math::Matrix3d R_n_w_ambf = quat_n_w_ambf.toMatrix();

        RigidBodyDynamics::Math::Vector3d P_n_w_ambf;
        P_n_w_ambf.setZero();
        
        P_n_w_ambf(0) = P_n_w_tf[0];
        P_n_w_ambf(1) = P_n_w_tf[1];
        P_n_w_ambf(2) = P_n_w_tf[2];

        const RigidBodyDynamics::Math::Matrix3d R_n_w_rbdl =
                                          CalcBodyWorldOrientation(*rbdlPSModel, Q, rbdlBodyId, true);
        const RigidBodyDynamics::Math::Vector3d P_n_0_rbdl = 
                                          CalcBodyToBaseCoordinates(*rbdlPSModel, Q, rbdlBodyId, 
                                              RigidBodyDynamics::Math::Vector3d(0., 0., 0.), true);

        const RigidBodyDynamics::Math::Vector3d P_n_w_rbdl = T_0_w.block<3, 3>(0, 0) * P_n_0_rbdl;

        CHECK_THAT(R_n_w_ambf, AllCloseMatrix(R_n_w_rbdl, TEST_PREC, TEST_PREC));
        CHECK_THAT(P_n_w_ambf, AllCloseMatrix(P_n_w_rbdl, TEST_PREC, TEST_PREC));
      }
    }
  }
}

/*
TEST_CASE_METHOD(ParallelStructure, __FILE__"_TestPSRandomPosition", "") 
{
  //mBody in RBDL has AMBF Joints
  std::map<std::string, unsigned int > mBodyNameMap = rbdlPSModel->mBodyNameMap;
  std::map<std::string, unsigned int>::iterator mBodyNameMapItr;
  for(mBodyNameMapItr = mBodyNameMap.begin(); mBodyNameMapItr != mBodyNameMap.end(); mBodyNameMapItr++)
  {
    std::string bodyName = mBodyNameMapItr->first;
    unsigned int bodyId = mBodyNameMapItr->second;
    std::string parentName = rbdlPSModel->GetBodyName(rbdlPSModel->GetParentBodyId(bodyId));
    std::cout << parentName << ", " << bodyName << ", " << bodyId << std::endl;
    
  }

  ForwardDynamics(*rbdlPSModel, Q, QDot, Tau, QDDot);
  std::vector<std::string> joints = baseHandler->get_joint_names();
  std::vector<std::string> baseChildren = baseHandler->get_children_names();

  CHECK (baseChildren.size() == Q.size());

  std::string activation_joint_name = "l3-l4";
  Q.setZero();

  std::unordered_map<std::string, float> q_desired;
  std::unordered_map<std::string, float>::iterator q_desiredItr;

  int activation_joint_id = baseHandler->get_joint_idx_from_name(activation_joint_name.c_str());
  std::cout << "activation_joint_id: " << activation_joint_id << std::endl;

  if(baseHandler->is_joint_idx_valid(activation_joint_id))
  {
    for(int nTest = 1; nTest <= 5; nTest++)
    {
      q_desired.clear();

      std::vector<float> joint_limit = PS_JOINT_LIMITS[activation_joint_name];
      float low = joint_limit.at(0);
      float high = joint_limit.at(1);

      q_desired[activation_joint_name] = EigenUtilities::get_random_between_range(low, high);
      usleep(1000000);

      for(int i = 0; i < 20; i++)
      {
        baseHandler->set_joint_pos<std::string>(activation_joint_name, q_desired[activation_joint_name]);
        usleep(250000);

        for(int i = 0; i < joints.size(); i++)
        {
          std::string joint = joints.at(i);
          std::string body = baseChildren.at(i);

          unsigned int rbdlBodyId = rbdlPSModel->GetBodyId(joint.c_str());
          float joint_angle = baseHandler->get_joint_pos<std::string>(joint);

          q_desired[body] = joint_angle;

        }
      }

      for(int i = 0; i < joints.size(); i++)
      {
        std::string joint = joints.at(i);
        std::string body = baseChildren.at(i);

        float joint_angle = q_desired[body];
        std::cout << "joint: " << joint << ", desired joint_angle: " << joint_angle << std::endl;
      }

      for(q_desiredItr = q_desired.begin(); q_desiredItr!=q_desired.end(); ++q_desiredItr)
      {
        std::string body = q_desiredItr->first;
        float joint_angle = q_desiredItr->second;

        unsigned int rbdlBodyId = rbdlPSModel->GetBodyId(body.c_str());
        if(rbdlBodyId != std::numeric_limits<unsigned int>::max() && rbdlBodyId < rbdlPSModel->mBodies.size())
        {
          rbdlBodyId--;
          Q[rbdlBodyId] = joint_angle;
        }
      }

      for(std::string body : baseChildren)
      {
        unsigned int rbdlBodyId = rbdlPSModel->GetBodyId(body.c_str());

        // AMBF body does not exist in RBDL model
        if(rbdlBodyId != std::numeric_limits<unsigned int>::max())
        // if(rbdlBodyId < rbdlPSModel->mBodies.size())
        {
          std::cout << "Executing Test case for body: "<< body << ", " << rbdlBodyId << std::endl;

          rigidBodyPtr rigidBodyHandler = clientPtr->getRigidBody(body, true);
          
          // n - respective body frame
          const tf::Quaternion quat_n_w_tf = rigidBodyHandler->get_rot();
          const tf::Vector3 P_n_w_tf = rigidBodyHandler->get_pos();

          RigidBodyDynamics::Math::Quaternion quat_n_w_ambf;
          quat_n_w_ambf(0) = quat_n_w_tf[0];
          quat_n_w_ambf(1) = quat_n_w_tf[1];
          quat_n_w_ambf(2) = quat_n_w_tf[2];
          quat_n_w_ambf(3) = quat_n_w_tf[3];

          const RigidBodyDynamics::Math::Matrix3d R_n_w_ambf = quat_n_w_ambf.toMatrix();

          RigidBodyDynamics::Math::Vector3d P_n_w_ambf;
          P_n_w_ambf.setZero();
          
          P_n_w_ambf(0) = P_n_w_tf[0];
          P_n_w_ambf(1) = P_n_w_tf[1];
          P_n_w_ambf(2) = P_n_w_tf[2];

          const RigidBodyDynamics::Math::Matrix3d R_n_w_rbdl =
                                            CalcBodyWorldOrientation(*rbdlPSModel, Q, rbdlBodyId, true);
          const RigidBodyDynamics::Math::Vector3d P_n_0_rbdl = 
                                            CalcBodyToBaseCoordinates(*rbdlPSModel, Q, rbdlBodyId, 
                                                RigidBodyDynamics::Math::Vector3d(0., 0., 0.), true);

          const RigidBodyDynamics::Math::Vector3d P_n_w_rbdl = T_0_w.block<3, 3>(0, 0) * P_n_0_rbdl;

          CHECK_THAT(R_n_w_ambf, AllCloseMatrix(R_n_w_rbdl, TEST_PREC, TEST_PREC));
          CHECK_THAT(P_n_w_ambf, AllCloseMatrix(P_n_w_rbdl, TEST_PREC, TEST_PREC));
        }
      }

      std::cout << "------- end of test: " << nTest << " ---------" << std::endl;
    }
  }
}
*/