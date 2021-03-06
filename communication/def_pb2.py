# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: def.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='def.proto',
  package='',
  syntax='proto2',
  serialized_options=None,
  serialized_pb=_b('\n\tdef.proto\"6\n\x0cSpeedCommand\x12\n\n\x02vx\x18\x01 \x02(\x02\x12\n\n\x02vy\x18\x02 \x01(\x02\x12\x0e\n\x06vtheta\x18\x03 \x02(\x02\"=\n\nOdomReport\x12\r\n\x05pos_x\x18\x01 \x02(\x02\x12\r\n\x05pos_y\x18\x02 \x02(\x02\x12\x11\n\tpos_theta\x18\x03 \x02(\x02')
)




_SPEEDCOMMAND = _descriptor.Descriptor(
  name='SpeedCommand',
  full_name='SpeedCommand',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='vx', full_name='SpeedCommand.vx', index=0,
      number=1, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='vy', full_name='SpeedCommand.vy', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='vtheta', full_name='SpeedCommand.vtheta', index=2,
      number=3, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=13,
  serialized_end=67,
)


_ODOMREPORT = _descriptor.Descriptor(
  name='OdomReport',
  full_name='OdomReport',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='pos_x', full_name='OdomReport.pos_x', index=0,
      number=1, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pos_y', full_name='OdomReport.pos_y', index=1,
      number=2, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pos_theta', full_name='OdomReport.pos_theta', index=2,
      number=3, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=69,
  serialized_end=130,
)

DESCRIPTOR.message_types_by_name['SpeedCommand'] = _SPEEDCOMMAND
DESCRIPTOR.message_types_by_name['OdomReport'] = _ODOMREPORT
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

SpeedCommand = _reflection.GeneratedProtocolMessageType('SpeedCommand', (_message.Message,), dict(
  DESCRIPTOR = _SPEEDCOMMAND,
  __module__ = 'def_pb2'
  # @@protoc_insertion_point(class_scope:SpeedCommand)
  ))
_sym_db.RegisterMessage(SpeedCommand)

OdomReport = _reflection.GeneratedProtocolMessageType('OdomReport', (_message.Message,), dict(
  DESCRIPTOR = _ODOMREPORT,
  __module__ = 'def_pb2'
  # @@protoc_insertion_point(class_scope:OdomReport)
  ))
_sym_db.RegisterMessage(OdomReport)


# @@protoc_insertion_point(module_scope)
