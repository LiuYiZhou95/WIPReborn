# ��¼

-	��game object���������ڣ���ʹ������ָ�룩
-	����object����ͬһ��world�����еĴ���ɾ��������world��sceneֻ��world��һ�������ڡ�.
-	��ͬcomponent֮����໥���ã�ֱ�ӵ�������Ϣ.
-	string�滻hash
-	�Ż�:WIPPhysicsManeger::update
				WIPSprite::rotate_to
				WIPSprite::translate_to
						WIPSprite::update_world(�ڵ㴢��ṹ���Ż���)
-	�Ĳ����Ż�����object�м�¼�Լ������Ĳ���λ�ã��ȼ��ý���Ƿ�仯���Ĳ���������û���ֻ����λ�ã��������Ĳ���������ɾ��������²��롣ע��󲿷ֶ����ǲ���仯�Ĳ�������ġ�
-	Collider��Mesh���룬Colliderʹ�òο�:
	```cpp
	void Collider::CreateRigidbody2D()
	{
		b2BodyDef bodyDef;
		bodyDef.type = IsKinematic ? b2_kinematicBody : b2_dynamicBody;
		bodyDef.userData = this;
		bodyDef.bullet = (Continuous_Collision?);
		bodyDef.linearDamping = LinearDrag;
		bodyDef.angularDamping = AngularDrag;
		bodyDef.gravityScale = GravityScale;
		bodyDef.fixedRotation = FixedAngle;
		bodyDef.allowSleep = SleepingMode != kNeverSleep2D;
		bodyDef.awake = m_SleepingMode != kStartAsleep2D;;
		//Fetch pose from transform (&bodyDef.position, &bodyDef.angle);
		// Create the body.
		_body = box2d_world->CreateBody (&bodyDef);
		// Calculate the collider body mass.
	}
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	```
	�����������������ж��collider��userdata����ΪCollider�������ñ任���������collider���������´���fixture�����´���fixture��ʹ��ĳЩ����ʧЧ��