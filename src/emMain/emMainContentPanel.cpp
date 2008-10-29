//------------------------------------------------------------------------------
// emMainContentPanel.cpp
//
// Copyright (C) 2007-2008 Oliver Hamann.
//
// Homepage: http://eaglemode.sourceforge.net/
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License version 3 as published by the
// Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License version 3 for
// more details.
//
// You should have received a copy of the GNU General Public License version 3
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <emCore/emRes.h>
#include <emMain/emMainContentPanel.h>
#include <emMain/emVirtualCosmos.h>


emMainContentPanel::emMainContentPanel(ParentArg parent, const emString & name)
	: emPanel(parent,name)
{
	SkyImage=emGetInsResImage(GetRootContext(),"emMain","Sky.tga",3);
	new emVirtualCosmosPanel(this,"");
	UpdateCoordinates();
	UpdateChildLayout();
}


emMainContentPanel::~emMainContentPanel()
{
}


emString emMainContentPanel::GetTitle()
{
	return "Eagle";
}


void emMainContentPanel::Layout(
	double layoutX, double layoutY, double layoutWidth, double layoutHeight,
	emColor canvasColor
)
{
	emPanel::Layout(layoutX,layoutY,layoutWidth,layoutHeight,canvasColor);

	//??? The following stuff has to be done "synchronously" here in
	//??? Layout() because this panel is used as the root panel of a
	//??? view with emView::VF_ROOT_SAME_TALLNESS. Otherwise the view
	//??? could choose a wrong visited panel while the tallness is
	//??? changed (happened when sizing the window very fast or when
	//??? iconifying the window on Windows). More or less, it's a bug
	//??? of emView.
	UpdateCoordinates();
	UpdateChildLayout();
}


bool emMainContentPanel::IsOpaque()
{
	return true;
}


void emMainContentPanel::Paint(const emPainter & painter, emColor canvasColor)
{
	painter.PaintImage(0,0,1,GetHeight(),SkyImage,255,canvasColor);
	PaintEagle(
		emPainter(
			painter,
			painter.GetClipX1(),
			painter.GetClipY1(),
			painter.GetClipX2(),
			painter.GetClipY2(),
			painter.GetOriginX()+painter.GetScaleY()*EagleShiftX,
			painter.GetOriginY()+painter.GetScaleY()*EagleShiftY,
			painter.GetScaleX()*EagleScaleX,
			painter.GetScaleY()*EagleScaleY
		)
	);
}


void emMainContentPanel::UpdateCoordinates()
{
	EagleScaleX=emMin(1.0/180000.0,GetHeight()/120000.0);
	EagleScaleY=EagleScaleX;
	EagleShiftX=0.5-EagleScaleX*78450.0;
	EagleShiftY=GetHeight()*0.5-EagleScaleY*47690.0;
	InvalidatePainting();
}


void emMainContentPanel::UpdateChildLayout()
{
	emPanel * p;
	double sz;

	p=GetChild("");
	if (!p) return;
	sz=40.0;
	p->Layout(
		(78450.0-sz*0.5)*EagleScaleX+EagleShiftX,
		(47690.0-sz*0.5)*EagleScaleY+EagleShiftY,
		sz*EagleScaleX,
		sz*EagleScaleY,
		0x000000ff
	);
}


void emMainContentPanel::PaintEagle(const emPainter & painter)
{
	static const double poly0[]={
		79695.0,46350.0,81090.0,46710.0,82980.0,48465.0,85185.0,49770.0,86580.0,50085.0,89595.0,49545.0,
		97785.0,45900.0,109215.0,39240.0,117990.0,32355.0,126270.0,26235.0,128925.0,24210.0,129060.0,24885.0,
		127935.0,25920.0,127665.0,26550.0,132480.0,22590.0,138735.0,16605.0,139995.0,14940.0,140580.0,13770.0,
		140850.0,12600.0,140940.0,11160.0,140850.0,9000.0,141660.0,9540.0,142065.0,10350.0,142335.0,12105.0,
		142650.0,11025.0,142785.0,8775.0,142740.0,6435.0,142425.0,4905.0,141615.0,3555.0,142470.0,3690.0,
		142920.0,3960.0,143685.0,4680.0,144135.0,5490.0,144450.0,6930.0,144585.0,8865.0,144540.0,10665.0,
		144180.0,12780.0,143595.0,14490.0,142740.0,16245.0,140175.0,19710.0,141210.0,19125.0,142245.0,18090.0,
		143505.0,16335.0,144450.0,14670.0,145530.0,11655.0,145980.0,9225.0,146025.0,8415.0,145935.0,6975.0,
		145710.0,6165.0,145215.0,5220.0,146610.0,6255.0,147060.0,6930.0,147240.0,7560.0,147375.0,9270.0,
		147285.0,10665.0,146925.0,12645.0,146160.0,14895.0,144990.0,17415.0,142785.0,21465.0,145440.0,18945.0,
		146520.0,17505.0,147825.0,15435.0,149040.0,12915.0,149265.0,11970.0,149355.0,10845.0,149850.0,11340.0,
		150165.0,12060.0,150300.0,13275.0,149850.0,15390.0,148950.0,17865.0,148365.0,19125.0,146160.0,22545.0,
		147555.0,21645.0,148410.0,20880.0,149220.0,19890.0,150435.0,17865.0,151065.0,16965.0,151245.0,17775.0,
		151110.0,18945.0,150660.0,20250.0,149895.0,21825.0,147645.0,25020.0,150255.0,23220.0,150840.0,22635.0,
		151470.0,21825.0,151740.0,22545.0,151740.0,23175.0,151560.0,23895.0,151200.0,24930.0,150480.0,25875.0,
		149400.0,26865.0,147105.0,28080.0,148815.0,28215.0,149670.0,28620.0,149850.0,29205.0,149580.0,30015.0,
		148950.0,30780.0,147600.0,31500.0,144990.0,31725.0,146655.0,32940.0,147060.0,33615.0,147150.0,34425.0,
		146745.0,35325.0,145755.0,35865.0,144540.0,35910.0,142155.0,35820.0,144405.0,37395.0,144720.0,38115.0,
		144450.0,38880.0,143595.0,39510.0,142650.0,39690.0,141660.0,39600.0,140265.0,39375.0,141660.0,40680.0,
		141975.0,41355.0,141885.0,42075.0,141435.0,42660.0,140760.0,42930.0,140175.0,42930.0,138735.0,42390.0,
		139185.0,43830.0,139185.0,44460.0,138870.0,45000.0,138195.0,45225.0,137385.0,45270.0,135675.0,44820.0,
		136710.0,46440.0,136845.0,47295.0,136755.0,48240.0,135855.0,48735.0,134910.0,48780.0,133875.0,48555.0,
		132390.0,47880.0,133515.0,49500.0,133830.0,50265.0,133650.0,51120.0,132930.0,51795.0,131805.0,51930.0,
		130005.0,51255.0,130635.0,53235.0,130545.0,54000.0,130050.0,54765.0,129105.0,55170.0,128250.0,54990.0,
		127260.0,54630.0,125550.0,53505.0,126495.0,55350.0,126675.0,56340.0,126450.0,57150.0,125685.0,57645.0,
		124875.0,57825.0,123705.0,57600.0,121635.0,56385.0,122625.0,58095.0,122940.0,58950.0,122850.0,59760.0,
		122400.0,60390.0,121320.0,60750.0,119790.0,60435.0,117855.0,58995.0,118800.0,61335.0,118800.0,62235.0,
		118215.0,63045.0,117180.0,63450.0,115875.0,63360.0,114885.0,62910.0,113760.0,61785.0,113895.0,63495.0,
		113850.0,64440.0,113355.0,65160.0,112635.0,65475.0,111645.0,65475.0,110835.0,65160.0,109620.0,64305.0,
		109890.0,66150.0,109845.0,66915.0,109440.0,67455.0,108720.0,67770.0,107685.0,67860.0,106515.0,67545.0,
		104985.0,66600.0,105390.0,67905.0,105300.0,68625.0,104805.0,69300.0,103995.0,69750.0,102825.0,69795.0,
		99540.0,68760.0,98640.0,69345.0,105615.0,71280.0,110340.0,72360.0,112815.0,73080.0,114615.0,73980.0,
		115650.0,74700.0,116055.0,75285.0,115965.0,75915.0,115425.0,76680.0,114615.0,77400.0,113355.0,77895.0,
		111600.0,78030.0,108900.0,77625.0,111600.0,78885.0,113130.0,79920.0,113670.0,80505.0,113715.0,81135.0,
		113355.0,81810.0,112725.0,82395.0,111600.0,82980.0,110430.0,83070.0,107325.0,82350.0,109350.0,83835.0,
		110115.0,84780.0,110295.0,85770.0,110025.0,86490.0,109395.0,87030.0,108405.0,87480.0,107145.0,87390.0,
		105660.0,86940.0,103050.0,85545.0,105210.0,88065.0,105750.0,88875.0,105840.0,89685.0,105660.0,90495.0,
		104985.0,91035.0,103680.0,91395.0,102420.0,91395.0,100980.0,90810.0,98505.0,88965.0,99540.0,91395.0,
		99585.0,92250.0,99360.0,93015.0,98415.0,94005.0,97380.0,94320.0,95805.0,94095.0,94590.0,93105.0,
		92700.0,90225.0,92610.0,92790.0,92340.0,93870.0,91575.0,94770.0,90315.0,95310.0,88920.0,95265.0,
		87705.0,94545.0,87210.0,93150.0,87120.0,90180.0,86175.0,93015.0,85455.0,93870.0,84330.0,94500.0,
		83115.0,94725.0,82215.0,94545.0,81405.0,93870.0,81045.0,92790.0,81135.0,91620.0,81855.0,89055.0,
		79605.0,91890.0,78570.0,92610.0,77535.0,93015.0,76005.0,92970.0,75195.0,92565.0,74835.0,91575.0,
		75105.0,90270.0,76815.0,87795.0,74520.0,89460.0,73125.0,90135.0,71730.0,90315.0,70605.0,90090.0,
		70020.0,89685.0,69885.0,89100.0,70110.0,88245.0,71685.0,85815.0,69435.0,87525.0,68175.0,87840.0,
		67275.0,87615.0,66240.0,86850.0,66060.0,86040.0,66285.0,85140.0,66870.0,84240.0,68580.0,82530.0,
		70605.0,80865.0,72990.0,79155.0,75510.0,76950.0,76950.0,75510.0,76590.0,74925.0,75465.0,76455.0,
		74790.0,76950.0,73980.0,76995.0,73170.0,76815.0,72630.0,76185.0,72000.0,74340.0,71505.0,75960.0,
		70965.0,76680.0,70155.0,76995.0,69210.0,76950.0,68400.0,76455.0,67905.0,75690.0,67590.0,74295.0,
		67275.0,76005.0,66960.0,76680.0,66285.0,77130.0,64980.0,77265.0,64260.0,77040.0,63765.0,76455.0,
		63405.0,74520.0,62280.0,76320.0,61605.0,76905.0,60660.0,77130.0,59805.0,76770.0,59175.0,76050.0,
		59175.0,73755.0,58140.0,75690.0,57240.0,76545.0,56520.0,76725.0,55710.0,76590.0,55080.0,76050.0,
		54585.0,75195.0,54270.0,73845.0,53190.0,75195.0,52425.0,75780.0,51615.0,75915.0,50805.0,75600.0,
		50355.0,74925.0,49770.0,73215.0,48825.0,74745.0,48285.0,75015.0,47160.0,75015.0,46305.0,74565.0,
		45675.0,73845.0,45360.0,72855.0,45360.0,71415.0,43875.0,73215.0,43155.0,73710.0,42165.0,73800.0,
		41040.0,73440.0,40455.0,72900.0,40095.0,72000.0,40275.0,70290.0,39015.0,72090.0,38385.0,72495.0,
		37710.0,72765.0,36990.0,72585.0,36180.0,71955.0,35865.0,71235.0,35910.0,69120.0,34830.0,70740.0,
		34290.0,71190.0,33345.0,71370.0,32355.0,70875.0,32040.0,70065.0,32130.0,68490.0,30780.0,69255.0,
		30015.0,69390.0,29205.0,69165.0,28620.0,68625.0,28530.0,67635.0,28800.0,66150.0,27135.0,67455.0,
		26235.0,67590.0,25110.0,67365.0,24570.0,66915.0,24300.0,66240.0,24435.0,65700.0,25785.0,63990.0,
		24030.0,65520.0,23085.0,65925.0,21735.0,65880.0,20970.0,65340.0,20925.0,64665.0,21375.0,63720.0,
		22185.0,62415.0,19800.0,63900.0,18810.0,64080.0,18000.0,63855.0,17010.0,63270.0,16740.0,62865.0,
		17055.0,62325.0,18225.0,61335.0,15975.0,61965.0,14985.0,61920.0,13905.0,61200.0,13725.0,60660.0,
		13905.0,60165.0,14355.0,59940.0,16605.0,59400.0,13725.0,59265.0,12060.0,58995.0,11250.0,58680.0,
		11250.0,58050.0,12330.0,57555.0,10215.0,56520.0,9225.0,55485.0,9180.0,54855.0,9495.0,54405.0,
		10215.0,54495.0,12465.0,55575.0,10485.0,53955.0,9180.0,53325.0,8370.0,52020.0,8010.0,50805.0,
		8235.0,50265.0,8910.0,51120.0,10035.0,51975.0,12600.0,53730.0,10440.0,51390.0,7785.0,49050.0,
		6930.0,47925.0,6660.0,46755.0,6705.0,45630.0,7065.0,44730.0,7560.0,44145.0,7605.0,45945.0,
		7740.0,46620.0,8280.0,47475.0,10620.0,49275.0,12600.0,50580.0,15750.0,52065.0,13275.0,49995.0,
		11610.0,48690.0,9945.0,47115.0,8730.0,45585.0,7740.0,44055.0,7290.0,42615.0,7245.0,41625.0,
		7425.0,40365.0,7695.0,39645.0,8325.0,38700.0,8685.0,38520.0,8370.0,39645.0,8235.0,40815.0,
		8415.0,41760.0,9405.0,43290.0,11160.0,45270.0,13500.0,47430.0,11880.0,45225.0,11520.0,44145.0,
		11520.0,43110.0,11700.0,42480.0,12105.0,41895.0,12690.0,41580.0,12465.0,43155.0,12735.0,44190.0,
		13590.0,45495.0,15120.0,46800.0,17055.0,47655.0,18765.0,48060.0,22545.0,48780.0,27000.0,49545.0,
		31140.0,50310.0,31725.0,50220.0,30330.0,49950.0,29340.0,49545.0,29700.0,49050.0,34515.0,49635.0,
		40410.0,50805.0,50130.0,51570.0,62865.0,53055.0,75510.0,52965.0,76500.0,51840.0,76635.0,51390.0,
		76635.0,51120.0,76455.0,51030.0,75195.0,51345.0,76230.0,48015.0,77940.0,46440.0
	};
	static const double poly1[]={
		48960.0,62550.0,47835.0,62910.0,46800.0,62415.0,45810.0,62505.0,45360.0,61830.0,45315.0,60885.0,
		43110.0,63090.0,41985.0,63045.0,41400.0,62460.0,40635.0,63360.0,39825.0,63360.0,39510.0,62370.0,
		37485.0,63630.0,36585.0,64350.0,35685.0,64125.0,34335.0,64035.0,33975.0,63225.0,35415.0,62325.0,
		35055.0,61920.0,33480.0,63180.0,32400.0,63135.0,32040.0,64170.0,31140.0,63990.0,30645.0,63000.0,
		31140.0,62145.0,30510.0,62055.0,29835.0,62685.0,29160.0,62235.0,28395.0,62010.0,28485.0,61425.0,
		30015.0,60660.0,30645.0,59625.0,29745.0,59805.0,29025.0,60525.0,27180.0,61065.0,26505.0,61470.0,
		25695.0,61110.0,25425.0,60210.0,26190.0,59580.0,26055.0,58905.0,24840.0,59625.0,24255.0,59670.0,
		24165.0,58860.0,23535.0,58275.0,24210.0,57915.0,24390.0,57150.0,24885.0,56250.0,26370.0,55800.0,
		27405.0,55620.0,27675.0,55035.0,26145.0,55170.0,24885.0,55530.0,24975.0,54720.0,26055.0,54540.0,
		26280.0,53865.0,25695.0,53415.0,26415.0,52605.0,27495.0,52425.0,28350.0,52200.0,29250.0,52740.0,
		29925.0,54450.0,30960.0,55035.0,32085.0,56205.0,34110.0,56520.0,35280.0,57285.0,36675.0,58140.0,
		39105.0,58500.0,40365.0,58725.0,41670.0,59715.0,43065.0,59535.0,44325.0,60705.0,45360.0,60705.0,
		47070.0,60975.0,48915.0,61785.0
	};
	static const double poly2[]={
		52965.0,62730.0,52290.0,63180.0,52290.0,63900.0,53145.0,64125.0,54000.0,64440.0,54135.0,63090.0
	};
	static const double poly3[]={
		61380.0,65520.0,63765.0,66330.0,65745.0,66510.0,64710.0,67545.0,63450.0,67950.0,62685.0,66960.0,
		60930.0,67095.0,60930.0,65745.0
	};
	static const double poly4[]={
		94185.0,68490.0,93915.0,70920.0,94995.0,71955.0,94500.0,72090.0,93330.0,71505.0,93150.0,73710.0,
		93960.0,75240.0,96525.0,77490.0,97335.0,78705.0,96480.0,78615.0,94185.0,76365.0,93555.0,76230.0,
		93330.0,76995.0,93015.0,76905.0,91800.0,74385.0,90000.0,72495.0,90000.0,74385.0,90540.0,76725.0,
		91845.0,78165.0,92115.0,79155.0,91170.0,79245.0,90540.0,77895.0,89730.0,77355.0,89280.0,78435.0,
		88740.0,79290.0,88155.0,79020.0,87390.0,77715.0,86940.0,76050.0,86310.0,74340.0,84600.0,72945.0,
		84960.0,74745.0,85635.0,76860.0,85410.0,78075.0,85185.0,77805.0,84555.0,78750.0,85050.0,79245.0,
		84825.0,80640.0,83880.0,80685.0,83520.0,80460.0,84735.0,79245.0,84465.0,78840.0,84195.0,78390.0,
		85095.0,77715.0,84600.0,76590.0,83610.0,75150.0,83160.0,73800.0,81315.0,72540.0,80550.0,72585.0,
		78840.0,74475.0,77985.0,74745.0,73620.0,79245.0,74250.0,80235.0,76275.0,77895.0,76905.0,77625.0,
		78975.0,75555.0,78840.0,76455.0,76860.0,78255.0,77580.0,78390.0,75510.0,80460.0,75285.0,81405.0,
		76140.0,81495.0,78840.0,78570.0,79335.0,78660.0,76635.0,82035.0,77490.0,82710.0,80640.0,79200.0,
		82575.0,76725.0,82710.0,77625.0,82170.0,78885.0,80505.0,80640.0,80415.0,81630.0,79110.0,83025.0,
		80055.0,84105.0,80685.0,83250.0,80775.0,84240.0,82350.0,83205.0,83115.0,82215.0,82800.0,83205.0,
		83205.0,83205.0,82800.0,84645.0,83565.0,85095.0,84690.0,83835.0,85725.0,81720.0,85545.0,82755.0,
		85320.0,83700.0,85950.0,84015.0,86535.0,85905.0,87840.0,85905.0,87750.0,84060.0,88110.0,83430.0,
		89190.0,84645.0,89280.0,85725.0,89910.0,86175.0,91080.0,85770.0,89910.0,84375.0,90585.0,83970.0,
		90765.0,82665.0,92070.0,85725.0,93150.0,85230.0,91710.0,82890.0,94410.0,85275.0,95310.0,83790.0,
		94815.0,82980.0,93240.0,82350.0,93915.0,80955.0,96300.0,83745.0,97065.0,82575.0,98325.0,82260.0,
		96075.0,80055.0,97380.0,80100.0,99135.0,81630.0,99585.0,81540.0,99765.0,81000.0,98685.0,80055.0,
		97290.0,78030.0,99000.0,79110.0,100935.0,80055.0,101070.0,79425.0,100485.0,78435.0,97515.0,76590.0,
		94680.0,73980.0,97470.0,75690.0,100440.0,77850.0,101115.0,77445.0,102690.0,78165.0,103140.0,77490.0,
		102735.0,76410.0,100935.0,75150.0,99855.0,74430.0,99855.0,73845.0,100620.0,73890.0,100935.0,74565.0,
		103635.0,76275.0,104580.0,75735.0,104985.0,74610.0,104040.0,73800.0,101250.0,72180.0,100035.0,71955.0,
		98775.0,71055.0,97785.0,71010.0,96390.0,69975.0,96660.0,69750.0,98730.0,70920.0,101430.0,71505.0,
		102195.0,71100.0,105615.0,73530.0,105390.0,71730.0,98460.0,69615.0,97155.0,68895.0,96300.0,69390.0,
		94860.0,69030.0
	};
	static const double poly5[]={
		111285.0,53595.0,112185.0,52830.0,113220.0,52110.0,113895.0,51255.0,114840.0,50265.0,115515.0,49905.0,
		115875.0,51030.0,115560.0,51345.0,114840.0,51345.0,114390.0,51795.0,115155.0,53010.0,114345.0,53325.0,
		114435.0,54135.0,113130.0,53460.0,112365.0,53775.0
	};
	static const double poly6[]={
		119205.0,46575.0,120555.0,45495.0,121860.0,43785.0,123840.0,42345.0,125235.0,41085.0,126135.0,39465.0,
		127350.0,38160.0,128160.0,36990.0,129150.0,36135.0,129915.0,34875.0,130365.0,33435.0,131175.0,32085.0,
		131355.0,30960.0,131760.0,29430.0,132030.0,28485.0,131985.0,27360.0,131895.0,26595.0,133065.0,26505.0,
		134055.0,26145.0,134100.0,26865.0,133245.0,27360.0,132975.0,28125.0,134775.0,27630.0,134910.0,28260.0,
		135495.0,28485.0,135315.0,29115.0,134325.0,29385.0,133830.0,29925.0,135315.0,29430.0,136080.0,29925.0,
		137970.0,29835.0,137430.0,30690.0,137610.0,31230.0,136080.0,31590.0,136350.0,32130.0,138150.0,32310.0,
		138060.0,33075.0,138555.0,33615.0,137205.0,34515.0,135000.0,34470.0,136800.0,35550.0,136575.0,36360.0,
		136980.0,36855.0,135540.0,37485.0,135675.0,38925.0,135270.0,39825.0,134325.0,39735.0,133740.0,39960.0,
		131310.0,38295.0,131850.0,39105.0,134100.0,40275.0,134685.0,41400.0,133785.0,41670.0,133065.0,42120.0,
		131625.0,41805.0,132075.0,42975.0,131265.0,43515.0,130725.0,44235.0,129555.0,44145.0,127980.0,42885.0,
		126945.0,42840.0,127845.0,44235.0,127440.0,45450.0,126720.0,45225.0,125685.0,45675.0,124065.0,44865.0,
		124425.0,46170.0,123705.0,46575.0,123165.0,47205.0,121770.0,46215.0,120105.0,46935.0
	};
	static const double poly7[]={
		79200.0,45945.0,80100.0,46035.0,80865.0,46215.0,81720.0,46620.0,82530.0,47250.0,83250.0,47970.0,
		84510.0,49005.0,85095.0,49365.0,85995.0,49635.0,86985.0,49590.0,88380.0,49230.0,93015.0,47385.0,
		97560.0,45135.0,102780.0,42165.0,108630.0,38700.0,113265.0,35685.0,117990.0,32355.0,126270.0,26235.0,
		117765.0,33345.0,113985.0,36315.0,109260.0,39690.0,103770.0,43110.0,97920.0,46485.0,94050.0,48465.0,
		90045.0,50265.0,88290.0,50670.0,86940.0,50760.0,85725.0,50535.0,84780.0,50085.0,83475.0,49275.0,
		82305.0,48285.0,81540.0,47790.0,80685.0,47655.0,80100.0,47655.0,79560.0,47880.0,79065.0,48240.0,
		78660.0,48330.0,78165.0,48330.0,77715.0,48195.0,77895.0,48060.0,78165.0,48150.0,78525.0,48150.0,
		78930.0,48060.0,79200.0,47835.0,79380.0,47610.0,79515.0,47295.0,79875.0,47115.0,80730.0,46935.0,
		79785.0,46800.0,79065.0,46755.0,78345.0,46800.0,77625.0,47070.0,77220.0,47385.0,76860.0,47790.0,
		76545.0,48240.0,76365.0,48060.0,75690.0,48510.0,75285.0,48960.0,74700.0,49770.0,74250.0,50625.0,
		74385.0,49860.0,74700.0,49095.0,75015.0,48645.0,75285.0,48330.0,75870.0,47835.0,76230.0,47250.0,
		76770.0,46665.0,77220.0,46350.0,77805.0,46080.0,78570.0,45945.0
	};
	static const double poly8[]={
		91260.0,77535.0,91710.0,76995.0,92790.0,76905.0,93330.0,77985.0,94995.0,79875.0,95355.0,81135.0,
		95805.0,82575.0,95805.0,83250.0,94860.0,83295.0,94320.0,82485.0,93690.0,81900.0,93780.0,83025.0,
		93960.0,83925.0,93420.0,84195.0,92745.0,83655.0,91890.0,81945.0,91755.0,80415.0,91755.0,78930.0
	};
	static const double poly9[]={
		86535.0,78210.0,87345.0,78300.0,87930.0,80100.0,88560.0,81225.0,89370.0,82305.0,89640.0,83385.0,
		89505.0,84645.0,88830.0,84780.0,87930.0,83880.0,87660.0,82350.0,87435.0,82395.0,87390.0,83745.0,
		87525.0,84645.0,86985.0,85140.0,86130.0,84645.0,85860.0,83340.0,85680.0,81540.0,85950.0,80145.0,
		85860.0,78705.0
	};
	static const double poly10[]={
		78570.0,48060.0,78975.0,47925.0,79155.0,47700.0,79200.0,47430.0,79065.0,47160.0,78660.0,47465.0,
		78750.0,47610.0,78750.0,47790.0,78615.0,47880.0,78390.0,47925.0,78210.0,47835.0,78120.0,47675.0,
		77850.0,47745.0,78030.0,47970.0,78210.0,48060.0
	};
	static const double poly11[]={
		34515.0,49635.0,40860.0,50670.0,50130.0,51570.0,55485.0,52020.0,63180.0,52425.0,69750.0,52470.0,
		75465.0,52245.0,76140.0,52065.0,76500.0,51840.0,76275.0,53100.0,76050.0,53415.0,75645.0,53550.0,
		69120.0,53730.0,63000.0,53640.0,56070.0,53190.0,49410.0,52515.0,43290.0,51615.0,40365.0,51075.0
	};
	static const double poly12[]={
		75465.0,51165.0,77760.0,49545.0,78570.0,49230.0,78750.0,49005.0,78570.0,49365.0,77760.0,49815.0,
		77490.0,50085.0,76770.0,50760.0,74970.0,51750.0,74835.0,51930.0,74880.0,52110.0,75240.0,52560.0,
		74970.0,52470.0,74565.0,52200.0,74295.0,51840.0,74205.0,51435.0,74205.0,50850.0,74340.0,50040.0,
		75240.0,48645.0,76230.0,47925.0,76905.0,48600.0,77130.0,49050.0,77445.0,49185.0,77985.0,49140.0,
		78705.0,48960.0,78570.0,49140.0,77715.0,49455.0
	};
	static const double poly13[]={
		78660.0,47465.0,
		78750.0,47610.0,
		78750.0,47790.0,
		78615.0,47880.0,
		78390.0,47925.0,
		78210.0,47835.0,
		78120.0,47675.0
	};
	static const double * const polys[]={
		poly0,poly1,poly2,poly3,poly4,poly5,poly6,poly7,poly8,poly9,poly10,poly11,poly12,poly13
	};
	static const int polySizes[]={
		461,74,6,8,151,15,71,70,18,19,15,18,27,7
	};
	static const emUInt32 polyColors[]={
		0x302030FF,0x303040FF,0x303040FF,0x303040FF,0x303040FF,0x303040FF,0x303040FF,
		0x508080FF,0x505030FF,0x505030FF,0x505030FF,0x508080FF,0x505030FF,0x000000FF
	};

	int i;

	for (i=0; i<14; i++) {
		painter.PaintPolygon(polys[i],polySizes[i],polyColors[i]);
	}
}
