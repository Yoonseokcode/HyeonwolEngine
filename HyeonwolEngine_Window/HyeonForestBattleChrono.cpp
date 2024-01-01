#pragma once
#include "HyeonForestBattleChrono.h"
#include "HyeonTransform.h"
#include "HyeonGameObject.h"
#include "HyeonForestBattleScene.h"
#include "HyeonTime.h"
#include "HyeonAnimator.h"
#include "HyeonInput.h"

namespace Hyeon
{
	HyeonForestBattleChrono::HyeonForestBattleChrono()
		:mChronoState(HyeonBattlePlayerScript::eState::DrawWeapon),
		 mUsedSkills(eUsedSkills::Attack), 
		 mAnimator(nullptr),
		 mTime(0.0f),
		 mHp(0),
		 mStamina(0)
	{
	}
	HyeonForestBattleChrono::~HyeonForestBattleChrono()
	{
	}
	void HyeonForestBattleChrono::Initialize()
	{
		HyeonBattlePlayerScript::Initialize();
	}
	void HyeonForestBattleChrono::Update()
	{
		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<HyeonAnimator>();

		switch (mChronoState)
		{
		case eState::DrawWeapon:
			afterDrawWeapon();
			break;
		case eState::Move:
			moving();
			break;
		case eState::Attack:
			break;
		case eState::Dead:
			break;
		default:
			assert(false);
			break;
		}
	}
	void HyeonForestBattleChrono::LateUpdate()
	{
		HyeonBattlePlayerScript::LateUpdate();
	}
	void HyeonForestBattleChrono::Render(HDC hdc)
	{
		HyeonBattlePlayerScript::Render(hdc);
	}
	void HyeonForestBattleChrono::OnCollisionEnter(HyeonCollider* other)
	{
		switch (mUsedSkills)
		{
		case eUsedSkills::Attack:
			mChronoState = eState::Attack;
			mAnimator->PlayAnimation(L"ChronoLeftAttack", false);
			
			/*HyeonTransform* tr = GetOwner()->GetComponent<HyeonTransform>();
			Vector2 pos = tr->GetPosition();

			pos.X -= playerToMonster.X;
			pos.Y -= playerToMonster.Y;*/

			break;
		case eUsedSkills::Skill1:
			mChronoState = eState::Attack;
			mAnimator->PlayAnimation(L"ChronoLeftSkill1", false);
			break;
		case eUsedSkills::Skill2:
			mChronoState = eState::Attack;
			mAnimator->PlayAnimation(L"ChronoLeftSkill2", false);
			break;
		default:
			break;
		}
	}
	void HyeonForestBattleChrono::OnCollisionStay(HyeonCollider* other)
	{
	}
	void HyeonForestBattleChrono::OnCollisionExit(HyeonCollider* other)
	{
		/*playerToMonster.X *= -1;
		playerToMonster.Y *= -1;

		mChronoState = HyeonBattlePlayerScript::eState::Move;

		moving();*/
	}
	void HyeonForestBattleChrono::afterDrawWeapon()
	{
		if (GetKeyState(VK_SPACE) & 0x8000 && 
			HyeonBattlePlayerScript::mChosenChar == HyeonBattlePlayerScript::eCharacter::Chrono)
		{
			mUsedSkills = eUsedSkills::Attack;
			playerToMonster = calculatingVector();
			mChronoState = HyeonBattlePlayerScript::eState::Move;
			moving();
		}
		else if (HyeonInput::GetKeyDown(eKeyCode::K) && 
			HyeonBattlePlayerScript::mChosenChar == HyeonBattlePlayerScript::eCharacter::Chrono)
		{
			mUsedSkills = eUsedSkills::Skill1;
			playerToMonster = calculatingVector();
			mChronoState = HyeonBattlePlayerScript::eState::Move;
			moving();
		}
		else if (HyeonInput::GetKeyDown(eKeyCode::L) && 
			HyeonBattlePlayerScript::mChosenChar == HyeonBattlePlayerScript::eCharacter::Chrono)
		{
			mUsedSkills = eUsedSkills::Skill2;
			playerToMonster = calculatingVector();
			mChronoState = HyeonBattlePlayerScript::eState::Move;
			moving();
		}
		else if (HyeonInput::GetKeyDown(eKeyCode::X) &&
			HyeonBattlePlayerScript::mChosenChar == HyeonBattlePlayerScript::eCharacter::Chrono)
		{
			mChronoState = HyeonBattlePlayerScript::eState::Dead;
			mAnimator->PlayAnimation(L"ChronoDead", false);
			mChosenChar = HyeonBattlePlayerScript::eCharacter::Ayla;
		}
	}
	void HyeonForestBattleChrono::afterAttack()
	{
	}
	void HyeonForestBattleChrono::moving()
	{
		//벡터로 이동해서 공격 구현 중
		HyeonTransform* tr = GetOwner()->GetComponent<HyeonTransform>();
		Vector2 pos = tr->GetPosition();

		//if (chosenChar)
		pos.X += playerToMonster.X * HyeonTime::GetDelataTime() * 700.0f;
		pos.Y += playerToMonster.Y * HyeonTime::GetDelataTime() * 700.0f;

		tr->SetPosition(pos);
	}
	Vector2 HyeonForestBattleChrono::calculatingVector()
	{
		HyeonTransform* tr = GetOwner()->GetComponent<HyeonTransform>();
		Vector2 pos = tr->GetPosition();

		Vector2 MonsterPos = HyeonForestBattleScene::GetMonsterPos();
		MonsterPos.X += 80.0f;
		MonsterPos.Y -= 50.0f;

		return (MonsterPos - pos).normalize();
	}
}