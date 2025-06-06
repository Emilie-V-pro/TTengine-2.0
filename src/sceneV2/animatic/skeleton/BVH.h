#ifndef __BVH_H__
#define __BVH_H__

#include <memory.h>
#include <string>
#include <vector>
#include <cassert>

#include <fstream>
#include <iostream>

#include "BVHAxis.h"
#include "BVHJoint.h"

/** @addtogroup BVH
@{
*/

namespace TTe {

	class BVHJoint;


	/** @brief Motion capture skeleton and animation
	*/
	class BVH
	{
		friend class TTe::BVHJoint;
	public:
		//! Default constructor
		BVH();
		//! Destructor
		BVH(const std::string& filename, bool enableEndSite=false)  { init(filename,enableEndSite); }
		~BVH() {}

		// copy constructor and operator

		BVH(const BVH& bvh){
			m_numFrames = bvh.m_numFrames;
			m_frameTime = bvh.m_frameTime;
			m_joints = bvh.m_joints;
			m_rootId = bvh.m_rootId;
		}

		BVH & operator=(const BVH & bvh){
			m_numFrames = bvh.m_numFrames;
			m_frameTime = bvh.m_frameTime;
			m_joints = bvh.m_joints;
			m_rootId = bvh.m_rootId;
			return *this;
		}

		//! init
		void init(const std::string& filename, bool enableEndSite=true);

		//! Return the number of frames
		int getNumberOfFrame(void) const	{ return m_numFrames;  }
		//! Return the dt between 2 frames
		float getFrameTime(void) const		{ return m_frameTime;  }

		//! Return the root joint
		const TTe::BVHJoint& getRoot(void) const;
		//! Return the root joint Id
		int getRootId(void) const { return m_rootId; }

		//! Return the number of joint
		int getNumberOfJoint(void) const	{ return (int)m_joints.size(); }
		//! Return the i-th joint
		TTe::BVHJoint& getJoint(int i) { assert(i >= 0); assert(i < (int)m_joints.size()); return m_joints[i]; }
		//! Return the i-th joint
		const TTe::BVHJoint& getJoint(int i) const  { assert(i >= 0); assert(i < (int)m_joints.size()); return m_joints[i]; }
		//! Return a joint Id fro mhis name, -& if the joint does not exist
		int getJointId(const std::string& name) const;
		//! Return the i-th joint
		TTe::BVHJoint& operator[](int i) { return getJoint(i); }
		//! Return the i-th joint
		const TTe::BVHJoint& operator[](int i) const { return getJoint(i); }
		//! create and add a joint, return the joint Id of the created joint
		int addJoint(const std::string& name, int parentId);



		//! Scaling the animation time
		void scaleAnimation(float factor);
		//! Scaling the skeleton
		void scaleSkeleton(float factor);
		//! Rotate the BVH
		void rotate90(TTe::AXIS axis, bool cw);
		//! Edit the animation in a multi resolution way
		void multiResEditAnimation(const std::vector<float>& coef);

		//! dump
		friend std::ostream& operator << (std::ostream& os, const BVH& bvh);

	protected:
		//! Number of frames
		int m_numFrames;
		//! Time between 2 frames
		float m_frameTime;

		//! Vector of joint
		std::vector<TTe::BVHJoint> m_joints;

		//! Root Joint
		//chara::BVHJoint* m_root;BVH bvh;
		long unsigned int m_rootId;


		//! internal init: recursive on the children
		void init(std::ifstream& stream, bool enableEndSite, int id);
        //! Return the best end name from it parent e.g. RHand from RWrist
		static std::string getEndSiteName(const std::string& parentName);


	private:
		//! Check if the next word in stream is word
		static bool expect(const std::string& word, std::ifstream& stream);
	};

} // namespace

/** @}
*/

#endif //__BVH_H__
