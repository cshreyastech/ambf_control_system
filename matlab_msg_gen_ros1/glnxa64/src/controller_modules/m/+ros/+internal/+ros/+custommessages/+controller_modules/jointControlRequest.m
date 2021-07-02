function [data, info] = jointControlRequest
%JointControl gives an empty data for controller_modules/JointControlRequest
% Copyright 2019-2020 The MathWorks, Inc.
%#codegen
data = struct();
data.MessageType = 'controller_modules/JointControlRequest';
[data.Header, info.Header] = ros.internal.ros.messages.std_msgs.header;
info.Header.MLdataType = 'struct';
[data.JointNames, info.JointNames] = ros.internal.ros.messages.ros.char('string',NaN);
[data.ControllerName, info.ControllerName] = ros.internal.ros.messages.ros.char('string',0);
[data.Desired, info.Desired] = ros.internal.ros.messages.trajectory_msgs.jointTrajectoryPoint;
info.Desired.MLdataType = 'struct';
[data.Actual, info.Actual] = ros.internal.ros.messages.trajectory_msgs.jointTrajectoryPoint;
info.Actual.MLdataType = 'struct';
info.MessageType = 'controller_modules/JointControlRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,24);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'joint_names';
info.MatPath{8} = 'controller_name';
info.MatPath{9} = 'desired';
info.MatPath{10} = 'desired.positions';
info.MatPath{11} = 'desired.velocities';
info.MatPath{12} = 'desired.accelerations';
info.MatPath{13} = 'desired.effort';
info.MatPath{14} = 'desired.time_from_start';
info.MatPath{15} = 'desired.time_from_start.sec';
info.MatPath{16} = 'desired.time_from_start.nsec';
info.MatPath{17} = 'actual';
info.MatPath{18} = 'actual.positions';
info.MatPath{19} = 'actual.velocities';
info.MatPath{20} = 'actual.accelerations';
info.MatPath{21} = 'actual.effort';
info.MatPath{22} = 'actual.time_from_start';
info.MatPath{23} = 'actual.time_from_start.sec';
info.MatPath{24} = 'actual.time_from_start.nsec';
