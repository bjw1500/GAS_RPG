// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGUserWidget.h"

void URPGUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

