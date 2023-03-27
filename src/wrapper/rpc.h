#pragma once

#define BASE_FIELD(s, f) \
			s->##f()
#define MUTABLE_FIELD(s, f) \
			s->mutable_##f()
#define BF BASE_FIELD
#define MF MUTABLE_FIELD


#define MUTABLE_FIELD_SET0(s, f0, ...) \
			s->set_##f0(__VA_ARGS__)
#define MUTABLE_FIELD_SET1(s, f0, f1, ...) \
			s->mutable_##f0()->set_##f1(__VA_ARGS__)
#define MUTABLE_FIELD_SET2(s, f0, f1, f2, ...) \
			s->mutable_##f0()->mutable_##f1()->set_##f2(__VA_ARGS__)
#define MUTABLE_FIELD_SET3(s, f0, f1, f2, f3, ...) \
			s->mutable_##f0()->mutable_##f1()->mutable_##f2()->set_##f3(__VA_ARGS__)
#define MFS0 MUTABLE_FIELD_SET0
#define MFS1 MUTABLE_FIELD_SET1
#define MFS2 MUTABLE_FIELD_SET2
#define MFS3 MUTABLE_FIELD_SET3