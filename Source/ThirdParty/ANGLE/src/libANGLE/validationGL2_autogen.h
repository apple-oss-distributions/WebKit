// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// validationGL2_autogen.h:
//   Validation functions for the OpenGL Desktop GL 2.x entry points.

#ifndef LIBANGLE_VALIDATION_GL2_AUTOGEN_H_
#define LIBANGLE_VALIDATION_GL2_AUTOGEN_H_

#include "common/PackedEnums.h"
#include "common/entry_points_enum_autogen.h"

namespace gl
{
class Context;

// GL 2.0
bool ValidateGetVertexAttribdv(const Context *context,
                               angle::EntryPoint entryPoint,
                               GLuint index,
                               GLenum pname,
                               const GLdouble *params);
bool ValidateVertexAttrib1d(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLdouble x);
bool ValidateVertexAttrib1dv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLdouble *v);
bool ValidateVertexAttrib1s(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLshort x);
bool ValidateVertexAttrib1sv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLshort *v);
bool ValidateVertexAttrib2d(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLdouble x,
                            GLdouble y);
bool ValidateVertexAttrib2dv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLdouble *v);
bool ValidateVertexAttrib2s(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLshort x,
                            GLshort y);
bool ValidateVertexAttrib2sv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLshort *v);
bool ValidateVertexAttrib3d(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLdouble x,
                            GLdouble y,
                            GLdouble z);
bool ValidateVertexAttrib3dv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLdouble *v);
bool ValidateVertexAttrib3s(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLshort x,
                            GLshort y,
                            GLshort z);
bool ValidateVertexAttrib3sv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLshort *v);
bool ValidateVertexAttrib4Nbv(const Context *context,
                              angle::EntryPoint entryPoint,
                              GLuint index,
                              const GLbyte *v);
bool ValidateVertexAttrib4Niv(const Context *context,
                              angle::EntryPoint entryPoint,
                              GLuint index,
                              const GLint *v);
bool ValidateVertexAttrib4Nsv(const Context *context,
                              angle::EntryPoint entryPoint,
                              GLuint index,
                              const GLshort *v);
bool ValidateVertexAttrib4Nub(const Context *context,
                              angle::EntryPoint entryPoint,
                              GLuint index,
                              GLubyte x,
                              GLubyte y,
                              GLubyte z,
                              GLubyte w);
bool ValidateVertexAttrib4Nubv(const Context *context,
                               angle::EntryPoint entryPoint,
                               GLuint index,
                               const GLubyte *v);
bool ValidateVertexAttrib4Nuiv(const Context *context,
                               angle::EntryPoint entryPoint,
                               GLuint index,
                               const GLuint *v);
bool ValidateVertexAttrib4Nusv(const Context *context,
                               angle::EntryPoint entryPoint,
                               GLuint index,
                               const GLushort *v);
bool ValidateVertexAttrib4bv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLbyte *v);
bool ValidateVertexAttrib4d(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLdouble x,
                            GLdouble y,
                            GLdouble z,
                            GLdouble w);
bool ValidateVertexAttrib4dv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLdouble *v);
bool ValidateVertexAttrib4iv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLint *v);
bool ValidateVertexAttrib4s(const Context *context,
                            angle::EntryPoint entryPoint,
                            GLuint index,
                            GLshort x,
                            GLshort y,
                            GLshort z,
                            GLshort w);
bool ValidateVertexAttrib4sv(const Context *context,
                             angle::EntryPoint entryPoint,
                             GLuint index,
                             const GLshort *v);
bool ValidateVertexAttrib4ubv(const Context *context,
                              angle::EntryPoint entryPoint,
                              GLuint index,
                              const GLubyte *v);
bool ValidateVertexAttrib4uiv(const Context *context,
                              angle::EntryPoint entryPoint,
                              GLuint index,
                              const GLuint *v);
bool ValidateVertexAttrib4usv(const Context *context,
                              angle::EntryPoint entryPoint,
                              GLuint index,
                              const GLushort *v);

// GL 2.1
}  // namespace gl

#endif  // LIBANGLE_VALIDATION_GL2_AUTOGEN_H_
