#include "Bullet.h"
#include "math.h"

#include "Arms/Weapon.h"
#define TAG_BULLET -1
Bullet* Bullet::create
(const char* bulletImageName, float flyingSpeed, Weapon* shooter, /*Entity* target,*/ WeaponBuff* buff) {
	Bullet* bullet = new(std::nothrow)Bullet;
	if (bullet && bullet->init(bulletImageName, flyingSpeed, shooter, /*target,*/ buff)) {
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;

}

bool Bullet::init
(const char* bulletImageName,  float flyingSpeed, Weapon* shooter, /*Entity* target,*/ WeaponBuff* buff) {
	if (!Sprite::init()) return false;


	setTexture(bulletImageName);
	setPosition(shooter->getVisiblePicture()->getPosition());

	setVisible(true);

	_attack = shooter->getWeaponAttack();
	_flyingSpeed = flyingSpeed;
	_shooter = shooter;
	/*_target = target;*/
	_buff = buff;

	
	//角度初始计算;
	auto shooterAngle = _shooter->getVisiblePicture()->getRotation();
	log("%f", shooterAngle);
	if (_shooter->getVisiblePictureSide() == "left") {
		if (shooterAngle >= -90 && shooterAngle <= 0) {
			_initAngle = (180.f - shooterAngle);
			setRotation(360.f - _initAngle);
		}
		else if (shooterAngle >= 0.f && shooterAngle <= 90.f) {
			_initAngle = 180.f - shooterAngle;//对于常规的逆时针正向图片（分左右）的
			setRotation( - _initAngle);			
		}
		else if (shooterAngle >= 270.f && shooterAngle <= 360.f) {
			_initAngle = 540.f - shooterAngle;
			setRotation(360.f - _initAngle);

		}
		else if (shooterAngle >= 360.f && shooterAngle <= 450.f) {
			_initAngle = 540.f - shooterAngle;
			setRotation(360.f - _initAngle);
		}
		else if (shooterAngle >= 630.f && shooterAngle <= 720.f) {
			_initAngle = 540.f - shooterAngle;
			setRotation(360.f - _initAngle);
		}
		
		//出现720度
		
	}
	else if (_shooter->getVisiblePictureSide() == "right") {
		if (shooterAngle >= -90 && shooterAngle <= 0) {
			_initAngle = -shooterAngle;
			setRotation(shooterAngle);
		}
		else if ((shooterAngle >= 0 && shooterAngle <= 90)||(shooterAngle>=270&&shooterAngle<=360)) {
			_initAngle = 360.f - shooterAngle;
			setRotation(shooterAngle);
		}
		else if ((shooterAngle >= 360.f && shooterAngle <= 450.f)) {
			_initAngle = 360.f - shooterAngle;
			setRotation(shooterAngle);
		}
		 
	}
	//转成弧度制
	_initAngle*=(PI/180);

	return true;
}

void Bullet::calPosition() {

	//if (!_target) {
		
		//TODO：帧率确认与同步问题，现在只有机械设置
	setPosition(getPosition() + 
		Vec2(cos(_initAngle) * _flyingSpeed / 60, sin(_initAngle) * _flyingSpeed / 60));
	
	//}
	//TODO:target不为空时,需要实体类的实现,瞄准实体类后的结果

}

void Bullet::calDistance() {
	//跟踪子弹
	/*if (!_target) {*/
		//TODO:需要Entity的获取位置函数，需要等后续完成
	/*}*/
}