#ifndef OCTOON_RIGIDBODY_COMPONENT_H_
#define OCTOON_RIGIDBODY_COMPONENT_H_

#include <memory>
#include <vector>
#include <octoon/game_component.h>
#include <octoon/physics_feature.h>
#include <octoon/collider_component.h>
#include <octoon/math/math.h>
#include <octoon/runtime/singleton.h>

#include <octoon/physics/physics_rigidbody.h>

namespace octoon
{
    enum class RigidbodySleepMode:int
    {
        NeverSleep, //RigidbodyComponent never automatically sleeps.
        StartAwake, //RigidbodyComponent is initially awake.
        StartAsleep, //RigidbodyComponent is initially asleep.
    };

    class OCTOON_EXPORT RigidbodyComponent final : public GameComponent, public physics::PhysicsListener
	{
		OctoonDeclareSubClass(RigidbodyComponent, GameComponent)
    public:
        RigidbodyComponent() noexcept;
		RigidbodyComponent(bool type) noexcept;
		RigidbodyComponent(bool type, float mass) noexcept;
        virtual ~RigidbodyComponent();
        virtual GameComponentPtr clone() const noexcept;

		void setPosition(const math::float3& position) noexcept;
		void setRotation(const math::Quaternion& quat) noexcept;

		void setGroupMask(std::uint16_t groupMask) noexcept;

        void setAngularVelocity(float v) noexcept;
        void setGravityScale(float scale) noexcept;
        void setMass(float m) noexcept;
        void setSleepMode(RigidbodySleepMode mode) noexcept;
        void setIsKinematic(bool type) noexcept;
        void setDynamicFriction(float f);
        void setStaticFriction(float f);
        void setRestitution(float f);
		void setLinearDamping(float value) noexcept;
		void setAngularDamping(float value) noexcept;

        float getDynamicFriction() const;
        float getStaticFriction() const;
        float getRestitution() const;
        float getAngularVelocity() const noexcept;
        float getGravityScale() const noexcept;
        float getMass() const noexcept;

		RigidbodySleepMode getSleepMode() const noexcept;

		bool getIsKinematic() const noexcept;

		std::shared_ptr<physics::PhysicsRigidbody> getRigidbody();

    private:
        virtual void onActivate() except override;
        virtual void onDeactivate() noexcept override;

        virtual void onAttachComponent(const GameComponentPtr& component) noexcept;
        virtual void onDetachComponent(const GameComponentPtr& component) noexcept;

		virtual void onFetchResult() noexcept override;

		virtual void onLayerChangeAfter() noexcept;
		virtual void onMoveAfter() noexcept;

		virtual void updateParentTransform() noexcept;

    private:
        bool isKinematic_;

        float angularVelocity_;
        float gravityScale_;
        float mass_;
        float dynamicFriction_;
        float staticFriction_;
        float restitution_;
		float linearDamping_;
		float angularDamping_;
		std::uint16_t groupMask_;

		math::float3 position_;
		math::float3 localPosition_;
		math::float3 scaling_;
		math::float3 localScaling_;
		math::Quaternion rotation_;
		math::Quaternion localRotation_;

		math::float4x4 transform_;
		math::float4x4 localTransform_;

        RigidbodySleepMode sleepMode_;

		std::shared_ptr<physics::PhysicsRigidbody> rigidbody_;
    };
}

#endif