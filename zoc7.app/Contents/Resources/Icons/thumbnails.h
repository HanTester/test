

#ifndef THUMBNAILS_H_INCLUDED
#define THUMBNAILS_H_INCLUDED

#pragma once

#define MSG_TNNEWDATA (WM_USER+1)
#define MSG_TNSUICIDE (WM_USER+2)
#define MSG_TNTOFRONT (WM_USER+3)

#define THUMBSTATE_HOT		1
#define THUMBSTATE_UPTODATE	2


class THUMBNAILS : public CHILDWINDOW {

	private:
			struct THUMBITEM {
				RECT Rect;
				ULONG State;
				MEMORYBITMAP *pMemoryBitmap;
				SESSION *pSession;
				WCHAR Title[128];
			};


	protected:	// members
			APP &App;

			MEMORYBITMAP MemoryBitmap;
			WINDOWFONT Font;

			int MsgOwnerNotify;
			BOOL KillPosted,
				 InPaint;

			int Rows,
				Cols,
				NumThumbs;

			SIZE ThumbSize;
			int FontHeight, FontBaseline;

			THUMBITEM Thumbs[64];


	protected:
			int CalcLayout(void);
			void DrawSessionThumb(SESSION *psession, MEMORYBITMAP &mbthumb);
			int FindHotThumb(void);

			void SetDirty(THUMBITEM &thumb, BOOL dirtystate)
					{ this->SetThumbFlag(thumb, THUMBSTATE_UPTODATE, !dirtystate); }
			BOOL IsDirty(THUMBITEM &thumb)
					{ return !this->IsThumbFlag(thumb, THUMBSTATE_UPTODATE); }

			void SetHot(THUMBITEM &thumb, BOOL hotstate)
					{ this->SetThumbFlag(thumb, THUMBSTATE_HOT, hotstate!=0); }
			BOOL IsHot(THUMBITEM &thumb)
					{ return this->IsThumbFlag(thumb, THUMBSTATE_HOT); }

			BOOL IsThumbFlag(THUMBITEM &thumb, ULONG flag)
					{ return (thumb.State & flag)!=0; }
			void SetThumbFlag(THUMBITEM &thumb, ULONG flag, int state)
					{ if (state) thumb.State|= flag; else thumb.State&= ~flag; }

			void InvalidateThumb(THUMBITEM &thumb)
					{ RECT r= this->ToHotRect(thumb.Rect); this->Invalidate(&r); }

			BOOL IsPointInRect(int x, int y, const RECT &r)
					{ return x>=r.left && x<=r.right && y>=r.top && y<=r.bottom; }
			BOOL IsRectInRect(const RECT &r, const RECT &rclip)
					{ return !(r.left>=rclip.right || r.right<=rclip.left || r.top>=rclip.bottom || r.bottom<=rclip.top); }


			// WINDOW callbacks
			virtual BOOL OnPaint(void);
			virtual BOOL OnSized(void);
			virtual BOOL OnTimer(int id);
			virtual BOOL OnMouseEvent(int event, int x, int y, int extra);
			virtual BOOL OnKeyboardEvent(const KEYBOARDEVENT &kbdevent);
			virtual BOOL OnFocusAcquired(void);
			virtual LRESULT OnUserMessage(int msg, WPARAM mp1, LPARAM mp2);



	public:
			THUMBNAILS(APP &app, int notifymsg, BOOL kbdinvoked= FALSE);
			virtual ~THUMBNAILS();

			void Resize(void);

			void SetDirty(SESSION *psession);
			RECT ToHotRect(RECT r);

			COLORREF GetBackgroundColor(void)
					{ return OSYS::GetSysColor(COLOR_3DFACE); }

			BOOL IsDead(void)
					{ return this->KillPosted; }
};



#endif // THUMBNAILS_H_INCLUDED
